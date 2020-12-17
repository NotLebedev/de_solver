#include <math.h>

#include "types.h"

data_t f1(data_t x, data_t y) {
    return -y / x;
}

data_t f2(data_t x, data_t y) {
    return 3 * x * sin(x) - y;
}

data_t f3(data_t x, data_t y) {
    return x * x * y + x * x;
}

data_t f4(data_t x, data_t y) {
    return (y - y * y) * x;
}

F2 functions_single[] = {f1, f2, f3, f4};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
data_t g11(data_t t, data_t x, data_t y) {
    return t + x - y * y + 2;
}

data_t g12(data_t t, data_t x, data_t y) {
    return sin(t - x) + 2.1 * y;
}

data_t g21(data_t t, data_t x, data_t y) {
    return -x - 5 * y;
}

data_t g22(data_t t, data_t x, data_t y) {
    return x + y;
}

data_t g31(data_t t, data_t x, data_t y) {
    return 4 * x + y - exp(2 * t);
}

data_t g32(data_t t, data_t x, data_t y) {
    return y - 2 * x;
}

F3 functions_double[][2] = {{g11, g12}, {g21, g22}, {g31, g32}};

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
    return 0.0;
}

data_t h22(data_t x) {
    return -6.0 / (x * x);
}

data_t h23(data_t x) {
    return 0;
}

data_t h31(data_t x) {
    return -2.0;
}

data_t h32(data_t x) {
    return 1.0;
}

data_t h33(data_t x) {
    return exp(x);
}

data_t h41(data_t x) {
    return 0.0;
}

data_t h42(data_t x) {
    return -1.0;
}

data_t h43(data_t x) {
    return 1 / x - 2 / (x * x * x);
}

F1 functions_coefs[][3] = {{h11, h12, h13},
                           {h21, h22, h23},
                           {h31, h32, h33},
                           {h41, h42, h43}};