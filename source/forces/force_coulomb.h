/****************************************************************
 *
 * force_coulomb.h
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

#ifdef FORCE_TYPE

ForceType(coulomb,ForceCoulomb)

#else

#ifndef PTF_FORCE_COULOMB_H
#define PTF_FORCE_COULOMB_H

#include "../force.h"

namespace POTFIT_NS {

  class ForceCoulomb : public Force {
  public:
    ForceCoulomb(class POTFIT *);
    virtual ~ForceCoulomb();

    void read_additional_data(FILE *);

    int num_slots(void);
    int neigh_type(void);

    int cols();
  };

}

#endif // PTF_FORCE_COULOMB_H

#endif // FORCE_TYPE
