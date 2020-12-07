#ifndef DE_SOLVER_RK_H
#define DE_SOLVER_RK_H

typedef double (*f2)(double, double);
typedef double (*f3)(double, double);

typedef enum {
    RK_2,
    RK_4
} Order;

double *rk_single(f2 func, Order order, double x0, double y0, double l, double n);
double *rk_double(f3 func, Order order, double x0, double y0, double l, double n);

#endif //DE_SOLVER_RK_H
