/****************************************************************
 *
 * neighbor_3.cpp:
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

#include "neighbor_3.h"

#include "../io.h"

using namespace POTFIT_NS;

Neighbor_3::Neighbor_3(POTFIT *ptf) :
  Neighbor(ptf)
{}

Neighbor_3::~Neighbor_3() {}

void Neighbor_3::init(Config *conf, int i, int j, vector *dd) {
  io->error << "The two-body neighbor function cannot be called for three-body neighbor lists!" << std::endl;
  io->pexit(EXIT_FAILURE);

  return;
}

void Neighbor_3::init(Config *conf, int i, int j, int k, vector *dd_ij, vector *dd_ik) {

  return;
}
