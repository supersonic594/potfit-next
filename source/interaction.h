/****************************************************************
 *
 * force.h:
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

#ifndef PTF_INTERACTION_H
#define PTF_INTERACTION_H

#include <cstdio>
#include <string>

#include "pointers.h"
#include "force.h"

namespace POTFIT_NS {

  class Interaction : protected Pointers {
  public:
    Interaction(class POTFIT *);
    ~Interaction();

    void init(void);
    double calc_forces(void);

    void set_type(const std::string &);
    std::string get_type(void);

    Force *force;

  private:
    class Force *init_force(const std::string &);

    std::string type;
  };
}

#endif // PTF_INTERACTION_H
