/****************************************************************
 *
 * force_pair.cpp:
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

#include <cstring>

#include "force_pair.h"
#include "../config.h"
#include "../io.h"
#include "../potential.h"
#include "../table.h"
#include "../tables/table_analytic.h"

using namespace POTFIT_NS;

ForcePair::ForcePair(POTFIT *ptf): Force(ptf) {
}

ForcePair::~ForcePair() {
}

int ForcePair::cols() {
  int n = config->ntypes;
  return (int)n*(n+1)/2.;
}

/****************************************************************
 *
 * ForcePair::read_additional_data(FILE *infile)
 * 	read the chemical potentials (if present)
 *
 ****************************************************************/

void ForcePair::read_additional_data(FILE *infile) {
  char  buffer[255], name[255];
  char *token;
  double val, min, max;
  int ret_val;

  if (potential->enable_cp) {

    // search for chempot keyword
    do {
      fscanf(infile, "%s", buffer);
    } while (strcmp(buffer, "chempot") != 0 && !feof(infile));

    potential->chem_pot = new TableAnalytic(ptf);
    potential->chem_pot->init_bare("chemical potentials",config->ntypes);

    // loop over all atom types
    for (int j = 0; j < config->ntypes; j++) {

      // read one line
      if (4 > fscanf(infile, "%s %lf %lf %lf", buffer, &val, &min, &max))
        io->error("Could not read chemical potential for %d. atomtype.", j);

      // split cp and _#
      token = strchr(buffer, '_');
      if (token != NULL) {
        strncpy(name, buffer, strlen(buffer) - strlen(token));
        name[strlen(buffer) - strlen(token)] = '\0';
      }
      if (strcmp("cp", name) != 0) {
        io->write("Found \"%s\" instead of \"cp\"\n", name);
        io->error("No chemical potentials found in potential file.\n");
      }
    potential->chem_pot->set_value(j, buffer, val, min, max);
    }
    io->write("- Enabled chemical potentials for %d elements.\n",config->ntypes);
  }

  return;
}
