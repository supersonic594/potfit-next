/****************************************************************
 *
 * opt_evo.h:
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

#ifdef OPTALG_TYPE

OptAlgType(evo,OptEvo)

#else

#ifndef PTF_OPT_EVO_H
#define PTF_OPT_EVO_H

#include "base_opt.h"

namespace POTFIT_NS {

  class OptEvo : public BaseOpt {
  public:
    OptEvo(class POTFIT *);
    ~OptEvo();

    void init(std::vector<std::string> &);
    void run(void);
  private:
    void init_population(double **, double *, double *);
    void opposite_check(double **, double *, int);

    // arrays for opposite check
    double *tot_cost;	// cost of two populations
    double **tot_P;	// two populations

    // sorting algorithms
    void quicksort(double *, int, int, double **);
    int partition(double *, int, int, int, double **);
    void swap_population(double *, double *);

    double evo_threshold;
    int maxsteps;
  };
}

#endif // PTF_OPT_EVO_H

#endif // OPTALG_TYPE
