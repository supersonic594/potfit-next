/****************************************************************
 *
 * table_tab3.cpp:
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

#include <cstdlib>
#include <cstring>
#include <limits>

#include "table_tab3.h"

#include "../io.h"
#include "../settings.h"

using namespace POTFIT_NS;

TableTab3::TableTab3(POTFIT *ptf) : Table(ptf) {
  return;
}

TableTab3::~TableTab3() {
  return;
}

void TableTab3::init(const std::string &name, const int &index) {
  return;
}

void TableTab3::read_potential(FILE *a) {
  return;
}

int TableTab3::get_number_params(void) {
  return num_params;
}

int TableTab3::get_number_free_params(void) {
  return num_free_params;
}

double TableTab3::get_cutoff(void) {
  return end;
}

double TableTab3::get_rmin(void) {
  return begin;
}

double TableTab3::get_val_min(const int &n) {
  return -std::numeric_limits<double>::infinity();
}

double TableTab3::get_val_max(const int &n) {
  return std::numeric_limits<double>::infinity();
}

double TableTab3::get_plotmin(void) {
  return 0.0;
}

double TableTab3::get_value(const double &r) {
  return 0.0;
}

void TableTab3::set_param(const int &i, const double& val) {
  return;
}

void TableTab3::update_potential(const int &update) {
  update_values();
  update_calc_table(update);

  return;
}

void TableTab3::update_values(void) {

  return;
}

void TableTab3::update_calc_table(const int &update) {

  return;
}

void TableTab3::update_slots(void) {

  return;
}

void TableTab3::write_potential(std::ofstream &outfile) {
}

void TableTab3::write_plot(FILE *outfile) {
}

void TableTab3::write_plotpoint(FILE *outfile) {
}
