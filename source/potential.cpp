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

#include <mpi.h>

#include "force.h"
#include "interaction.h"
#include "io.h"
#include "memory.h"
#include "potential.h"
#include "templates.h"

#include "tables/table.h"
#include "tables/list_tables.h"

using namespace POTFIT_NS;

Potential::Potential(POTFIT *ptf) : Pointers(ptf) {
  enable_cp = 0;
  num_globals = 0;

  num_pots = 0;
  num_free_pots = 0;

  num_params = 0;
  num_free_params = 0;

  invar_pot = NULL;

  idxpot = NULL;
  idxparam = NULL;

  rcut_max = 0.0;

  pots = NULL;
  global_params = NULL;
  chem_pot = NULL;
  calc_pot = NULL;

  return;
}

Potential::~Potential() {
  delete [] invar_pot;

  if (global_params)
    delete global_params;

  if (chem_pot)
    delete chem_pot;

  return;
}

void Potential::init(int size) {
  num_pots = size;
  num_free_pots = size;
  invar_pot = new int[interaction->force->cols()];
  for (int i=0;i<interaction->force->cols();i++)
    invar_pot[i] = 0;

  return;
}

void Potential::read_globals(FILE *infile) {
  char  buffer[255], name[255];
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
    if (2 > fscanf(infile, "%s %d", buffer, &num_globals))
      io->error("Global parameters are missing in the potential file.");

    global_params = new GlobalsTable(ptf, num_globals);

    // read the global parameters
    for (int j = 0; j < num_globals; j++) {
      ret_val = fscanf(infile, "%s %lf %lf %lf", name, &val, &min, &max);
      if (4 > ret_val)
        if (strcmp(name, "type") == 0) {
          sprintf(buffer, "Not enough global parameters!\n");
          io->error("%sYou specified %d parameter(s), but needed are %d.\nAborting", buffer, j, num_globals);
        }
      global_params->add_param(j, name, val, min, max);
    }
  }
  io->write("- Read %d global parameters\n", num_globals);

  num_params += global_params->get_number_params();

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
    if (2 > fscanf(infile, "%s %s", buffer, name))
      io->error("Premature end of potential file!");
    if (strcmp(buffer, "type") != 0)
      io->error("Unknown keyword in potential file, expected \"type\" but found \"%s\".", buffer);
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
    rcut_max = MAX(rcut_max, pots[i]->get_cutoff());
  }
  io->write("- Sucessfully read %d potentials\n", num_pots);

  return;
}

void Potential::create_indirect_index(void) {
  int i, j;

}
