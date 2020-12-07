#ifndef DE_SOLVER_RK_H
#define DE_SOLVER_RK_H

typedef double (*f2)(double, double);
typedef double (*f3)(double, double, double);

typedef struct {
    double x;
    double y;
} Vector2D;

typedef enum {
    RK_2,
    RK_4
} Order;

double *rk_single(f2 func, Order order, double x0, double y0, double l, size_t n);
Vector2D *rk_double(f3 func1, f3 func2, Order order, double t0, double x0, double y0, double l, size_t n);

#endif //DE_SOLVER_RK_H
