#ifndef DE_SOLVER_RK_H
#define DE_SOLVER_RK_H

#include <stddef.h>

typedef double (*F2)(double, double);
typedef double (*F3)(double, double, double);

typedef struct {
    double x;
    double y;
} Vector2D;

typedef enum {
    RK_2,
    RK_4
} Order;

double *rk_single(F2 func, Order order, double x0, double y0, double l, size_t n);
Vector2D *rk_double(F3 func1, F3 func2, Order order, double t0, double x0, double y0, double l, size_t n);

#endif //DE_SOLVER_RK_H
