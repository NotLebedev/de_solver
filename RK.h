#ifndef DE_SOLVER_RK_H
#define DE_SOLVER_RK_H

#include "types.h"

typedef enum {
    RK_2,
    RK_4
} Order;

data_t *rk_single(F2 func, Order order, data_t x0, data_t y0, data_t l, size_t n);
Vector2D *rk_double(F3 func1, F3 func2, Order order, data_t t0, data_t x0, data_t y0, data_t l, size_t n);

#endif //DE_SOLVER_RK_H
