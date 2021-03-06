/****************************************************************
 *
 * func_kawamura.cpp:
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

#include "func_kawamura.h"

#include "../utils.h"

using namespace POTFIT_NS;

FuncKAWAMURA::FuncKAWAMURA() : r6(0.0) {}

FuncKAWAMURA::~FuncKAWAMURA() {}

int FuncKAWAMURA::num_params(void) {
  return 9;
}

void FuncKAWAMURA::calc(const double &r, const std::vector<double> &p, double *f) {
  r6 = r * r * r;
  r6 *= r6;

  *f = p[0] * p[1] / r + p[2] * (p[5] + p[6]) * exp((p[3] + p[4] - r) / (p[5] + p[6])) - p[7] * p[8] / r6;

  return;
}
