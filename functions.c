#include <math.h>

#include "RK.h"

double f1(double x, double y) {
    return - y / x;
}

f2 functions_single[] = {f1};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double g11(double t, double x, double y) {
    return t + x - y * y + 2;
}

double g12(double t, double x, double y) {
    return sin(t - x) + 2.1 * y;
}

f3 functions_double[][2]= {{g11, g12}};