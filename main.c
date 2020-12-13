#include <stdio.h>
#include <math.h>

#include "RK.h"
#include "boundary.h"

double h1(double x) {
    return -3 * x;
}

double h2(double x) {
    return 2.0;
}

double h3(double x) {
    return 1.5;
}

int main(void) {
    f1 coefs[3] = {h1, h2, h3};
    Vector2D init[3] = {{0.0, 0.5}, {1.0, 1.0}, {1.3, 2.0}};
    double *res = boundary(0.7, 1.0, coefs, init, 3000);

    for (size_t i = 0; i < 3001; i++) {
        printf("%lf %lf\n", 0.7 + (1.0 - 0.7) / 3000 * i, res[i]);
    }
    return 0;
}
