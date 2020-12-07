#include <stdio.h>

#include "RK.h"

double f(double x, double y) {
    return - y / x;
}

int main() {
    double *res = rk_single(f, RK_4, 1.0, 3.0, 5.0, 30);

    for (size_t i = 0; i < 31; i++) {
        printf("%lf %lf\n", 1.0 + i * (5.0 / 30), res[i]);
    }
    return 0;
}
