/****************************************************************
 *
 * elstat_table.h:
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

#ifndef PTF_ELSTAT_TABLE_H
#define PTF_ELSTAT_TABLE_H

#include <iostream>

#include "../pointers.h"

namespace POTFIT_NS {

  class ElstatTable : protected Pointers {
  public:
    ElstatTable(class POTFIT *);
    ~ElstatTable();

  private:
    // coulomb parameters
    double *ratio;
    double *charge;
    double last_charge;
    double *dp_kappa;
    int sw_kappa;

    // dipole parameters
    double *dp_alpha;
    double *dp_b;
    double *dp_c;
  };
}

#endif // PTF_ELSTAT_TABLE_H
