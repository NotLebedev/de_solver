#ifndef DE_SOLVER_TYPES_H
#define DE_SOLVER_TYPES_H

#include <stddef.h>

typedef double data_t;

typedef data_t (*F1)(data_t);
typedef data_t (*F2)(data_t , data_t);
typedef data_t (*F3)(data_t , data_t , data_t);

typedef struct {
    data_t x;
    data_t y;
} Vector2D;

#endif //DE_SOLVER_TYPES_H
