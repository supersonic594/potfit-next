/****************************************************************
 *
 * output.cpp:
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

#include "output.h"

using namespace POTFIT_NS;

Output::Output(POTFIT *ptf) : Pointers(ptf) {
  strcpy(distfile, "\0");
  strcpy(endpot, "\0");
  strcpy(imdpot, "\0");
  strcpy(lammpspot, "\0");
  strcpy(output_prefix, "\0");
  strcpy(plotfile, "\0");
  strcpy(plotpointfile, "\0");
  strcpy(tempfile, "\0");

  imdpotsteps = 1000;
  enable_distfile = 0;
  enable_output_files = 0;
  enable_imd_pot = 0;
  enable_lammps_pot = 0;
  enable_plot_file = 0;
  enable_log = 0;

  plotmin = 0.1;

  return;
}

Output::~Output() {
  return;
}

void Output::write_tempfile(void) {
  return;
}
