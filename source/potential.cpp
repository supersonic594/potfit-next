/****************************************************************
 *
 * potential.cpp:
 *
 ****************************************************************
 *
 * Copyright 2002-2013
 *	Institute for Theoretical and Applied Physics
 *	University of Stuttgart, D-70550 Stuttgart, Germany
 *	http://potfit.itap.physik.uni-stuttgart.de/
 *
 ****************************************************************
 *
 *   This file is part of potfit.
 *
 *   potfit is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   potfit is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with potfit; if not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************/

#include <algorithm>

#include "force.h"
#include "interaction.h"
#include "io.h"
#include "memory.h"
#include "potential.h"
#include "structures.h"

#include "tables/table.h"
#include "tables/list_tables.h"

using namespace POTFIT_NS;

Potential::Potential(POTFIT *ptf) :
  Pointers(ptf),
  num_globals(0),
  num_pots(0),
  num_free_pots(0),
  invar_pot(NULL),
  idxpot(NULL),
  idxparam(NULL),
  rcut(NULL),
  rmin(NULL),
  rcut_min(0.0),
  rcut_max(0.0),
  pots(NULL),
  opt(NULL),
  global_params(NULL),
  chem_pot(NULL),
  enable_cp(0),
  num_params(0),
  num_free_params(0)
{}

Potential::~Potential() {
  if (NULL != invar_pot)
    delete [] invar_pot;
  if (NULL != rcut)
    delete [] rcut;
  if (NULL != rmin)
    delete [] rmin;
  if (NULL != idxpot)
    delete [] idxpot;
  if (NULL != idxparam)
    delete [] idxparam;

  for (unsigned i = 0; i < elements.size(); ++i)
    delete [] elements[i];
  elements.clear();

  if (NULL != pots) {
    for (int i=0; i<num_pots; i++)
      delete pots[i];
    delete [] pots;
  }
  if (NULL != opt)
    delete opt;

  if (NULL != global_params)
    delete global_params;

  if (NULL != chem_pot)
    delete chem_pot;

  if (NULL != xcoord)
    delete [] xcoord;

  if (NULL != table)
    delete [] table;

  if (NULL != d2tab)
    delete d2tab;

  return;
}

void Potential::init(const int &size) {
  const int cols = interaction->force->cols();

  num_pots = size;
  num_free_pots = size;
  invar_pot = new int[cols];
  xcoord = new double[cols * POT_STEPS];
  table = new double[cols * POT_STEPS];
  d2tab = new double[cols * POT_STEPS];
  for (int i=0; i<interaction->force->cols(); i++)
    invar_pot[i] = 0;
  for (int i = 0; i < structures->get_ntypes(); ++i) {
    elements.push_back(new char[11]);
    sprintf(elements[i],"%d",i);
  }

  return;
}

void Potential::read_globals(FILE *infile) {
  char  buffer[1024], name[255];
  double val, min, max;
  int ret_val;
  fpos_t filepos;

  do {
    fgetpos(infile, &filepos);
    ret_val = fscanf(infile, "%s", buffer);
  } while (strcmp(buffer, "globals") != 0 && !feof(infile));
  fsetpos(infile, &filepos);

  // check for global keyword
  if (strcmp(buffer, "globals") == 0) {
    if (2 > fscanf(infile, "%s %d", buffer, &num_globals)) {
      io->error << "Global parameters are missing in the potential file." << std::endl;
      io->pexit(EXIT_FAILURE);
    }

    global_params = new GlobalsTable(ptf, num_globals);

    // read the global parameters
    for (int j = 0; j < num_globals; j++) {
      ret_val = fscanf(infile, "%s %lf %lf %lf", name, &val, &min, &max);
      if (4 > ret_val)
        if (strcmp(name, "type") == 0) {
          io->error << "Not enough global parameters!" << std::endl;
          io->error << "You specified " << j << " parameter(s), but needed are " << num_globals << "." << std::endl;
          io->pexit(EXIT_FAILURE);
        }
      global_params->add_param(j, name, val, min, max);
    }
  } else {
    global_params = new GlobalsTable(ptf, 0);
  }

  io->write << "- Read " << num_globals << " global parameters" << std::endl;

  num_params += global_params->get_number_params();
  num_free_params += global_params->get_number_free_params();

  return;
}

void Potential::read_potentials(FILE *infile) {
  char  buffer[255], name[255];
  int   ret_val;
  fpos_t filepos;

  pots = new Table*[num_pots];

  for (int i=0; i<num_pots; i++) {
    do {
      fgetpos(infile, &filepos);
      ret_val = fscanf(infile, "%s", buffer);
    } while (strcmp(buffer, "type") != 0 && !feof(infile));
    fsetpos(infile, &filepos);
    // read type
    if (2 > fscanf(infile, "%s %s", buffer, name)) {
      io->error << "Premature end of potential file!" << std::endl;
      io->pexit(EXIT_FAILURE);
    }
    if (strcmp(buffer, "type") != 0) {
      io->error << "Unknown keyword in potential file, expected \"type\" but found \"" << buffer << "\"." << std::endl;
      io->pexit(EXIT_FAILURE);
    }
    if (strcmp(buffer, "table3") == 0) {
      pots[i] = new TableTab3(ptf);
    } else if (strcmp(buffer, "table4") == 0) {
      pots[i] = new TableTab4(ptf);
    } else
      pots[i] = new TableAnalytic(ptf);
    pots[i]->init(name, i);
    pots[i]->read_potential(infile);

    num_params += pots[i]->get_number_params();
    if (invar_pot[i] == 0)
      num_free_params += pots[i]->get_number_free_params();
    rcut_min = std::min(rcut_min, pots[i]->get_rmin());
    rcut_max = std::max(rcut_max, pots[i]->get_cutoff());
  }
  rcut = new double[square(structures->get_ntypes())];
  rmin = new double[square(structures->get_ntypes())];

  // TODO: this only works for pair interactions
  for (int i=0; i<structures->get_ntypes(); i++) {
    for (int j=0; j<structures->get_ntypes(); j++) {
      int k = (i <= j) ? i * structures->get_ntypes() + j - ((i * (i + 1)) / 2)
              : j * structures->get_ntypes() + i - ((j * (j + 1)) / 2);
      rcut[i*structures->get_ntypes()+j] = pots[k]->get_cutoff();
      rmin[i*structures->get_ntypes()+j] = pots[k]->get_rmin();
    }
  }

  io->write << "- Sucessfully read " << num_pots << " potentials" << std::endl;

  opt = new OptTable(ptf, num_free_params);
  init_opt_table();

  return;
}

void Potential::write_potentials(std::ofstream &outfile) {

  // write header
  write_potential_header(outfile);

  // write tables
  if (global_params->get_number_free_params() > 0)
    global_params->write_potential(outfile);

  if (NULL != chem_pot)
    chem_pot->write_potential(outfile);

  for (int i=0;i<num_pots;i++)
    pots[i]->write_potential(outfile);

  return;
}

void Potential::init_opt_table(void) {
  int count = 0, loc_count = 0;
  double temp[3];

  idxpot = new int[num_free_params];
  idxparam = new int[num_free_params];

  for (int i=0; i<num_pots; i++) {
    if (0 == invar_pot[i]) {
      loc_count = 0;
      pots[i]->opt_pot_start = count;
      for (int j=0; j<pots[i]->get_number_params(); j++) {
        if (pots[i]->invar_par[j] == 0) {
          idxpot[count] = i;
          idxparam[count] = j;
	  pots[i]->idx[loc_count++] = j;
	  opt->val_min[count] = pots[i]->get_val_min(j);
	  opt->val_max[count] = pots[i]->get_val_max(j);
          opt->values[count++] = pots[i]->values[j];
        }
      }
    }
  }
  global_params->set_opt_pot_start(count);
  for (int i=0;i<global_params->get_number_params();i++) {
    idxpot[count] = num_pots;
    idxparam[count] = i;
    global_params->get_value(i,temp);
    opt->val_min[count] = temp[1];
    opt->val_max[count] = temp[2];
    opt->values[count++] = temp[0];
  }

  if (count != num_free_params) {
    io->error << "Number of free parameters is inconsistent!" << std::endl;
    io->pexit(EXIT_FAILURE);
  }

  return;
}

void Potential::update_potentials(const int &update) {
  if (NULL == opt->val_p)
    opt->val_p = opt->values;
  if (global_params->get_number_free_params() > 0)
    global_params->update_potentials();
  for (int i=0; i<num_pots; i++) {
    if (0 == invar_pot[i] || update)
      pots[i]->update_potential(update);
  }
  opt->val_p = opt->values;

  return;
}

void Potential::update_slots(void) {
  for (int i=0; i<num_pots; i++) {
    pots[i]->update_slots();
  }

  return;
}

void Potential::set_enable_cp(const int &i) {
  enable_cp = i;

  return;
}

int Potential::get_enable_cp(void) {
  return enable_cp;
}

void Potential::write_potential_header(std::ofstream &outfile) {
  outfile << "#F 0 " << interaction->force->cols() << std::endl;
  outfile << "#T " << interaction->get_type() << std::endl;
  outfile << "#C";
  for (unsigned int i=0;i<elements.size();i++)
    outfile << " " << elements[i];
  outfile << std::endl;
  outfile << "#I";
  for (int i=0;i<interaction->force->cols();i++)
    outfile << " " << invar_pot[i];
  outfile << std::endl;
  outfile << "#G";
  for (int i=0;i<interaction->force->cols();i++)
    outfile << " " << invar_pot[i];
  outfile << std::endl;
  outfile << "#E" << std::endl;

  return;
}

int Potential::get_num_params(void) {
  return num_params;
}

int Potential::get_num_free_params(void) {
  return num_free_params;
}

int Potential::get_format(const int &index) {
  if (index < num_pots)
    return pots[index]->format;
  // everything else but regular potentials are analytic potentials
  else
    return 0;
}
