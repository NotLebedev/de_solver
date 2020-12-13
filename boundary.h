#ifndef DE_SOLVER_BOUNDARY_H
#define DE_SOLVER_BOUNDARY_H

#include <stddef.h>
#include "RK.h"

typedef double (*F1)(double);

double *boundary(double x_0, double x_n, F1 eq_coef[3], Vector2D init_coef[3], size_t n);

#endif //DE_SOLVER_BOUNDARY_H
