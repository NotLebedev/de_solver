#include <math.h>

#include "RK.h"
#include "boundary.h"

double f1(double x, double y) {
    return - y / x;
}

F2 functions_single[] = {f1};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double g11(double t, double x, double y) {
    return t + x - y * y + 2;
}

double g12(double t, double x, double y) {
    return sin(t - x) + 2.1 * y;
}

F3 functions_double[][2]= {{g11, g12}};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double h11(double x) {
    return -3 * x;
}

double h12(double x) {
    return 2.0;
}

double h13(double x) {
    return 1.5;
}

double h21(double x) {
    return -1.0;
}

double h22(double x) {
    return 0;
}

double h23(double x) {
    return 0;
}

F1 functions_coefs[][3] = {{h11, h12, h13}, {h21, h22, h23}};