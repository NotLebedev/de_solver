#ifndef DE_SOLVER_BOUNDARY_H
#define DE_SOLVER_BOUNDARY_H

#include "types.h"

data_t *boundary(data_t x_0, data_t x_n, F1 eq_coef[3], Vector2D init_coef[3], size_t n);

#endif //DE_SOLVER_BOUNDARY_H
