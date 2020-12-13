#include <math.h>

#include "types.h"

data_t f1(data_t x, data_t y) {
    return -y / x;
}

F2 functions_single[] = {f1};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
data_t g11(data_t t, data_t x, data_t y) {
    return t + x - y * y + 2;
}

data_t g12(data_t t, data_t x, data_t y) {
    return sin(t - x) + 2.1 * y;
}

F3 functions_double[][2] = {{g11, g12}};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
data_t h11(data_t x) {
    return -3 * x;
}

data_t h12(data_t x) {
    return 2.0;
}

data_t h13(data_t x) {
    return 1.5;
}

data_t h21(data_t x) {
    return -1.0;
}

data_t h22(data_t x) {
    return 0;
}

data_t h23(data_t x) {
    return 0;
}

F1 functions_coefs[][3] = {{h11, h12, h13},
                           {h21, h22, h23}};