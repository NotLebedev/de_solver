#include <stdio.h>
#include <math.h>

#include "RK.h"

double f(double x, double y) {
    return - y / x;
}

double g1(double t, double x, double y) {
    return t + x - y * y + 2;
}

double g2(double t, double x, double y) {
    return sin(t - x) + 2.1 * y;
}

int main(void) {
    double *res = rk_single(f, RK_4, 1.0, 3.0, 5.0, 30);

    Vector2D *res2 = rk_double(g1, g2, RK_4, 0, 1.5, 0, 5.0, 300);

    for (size_t i = 0; i < 301; i++) {
        //printf("%lf %lf\n", 1.0 + i * (5.0 / 30), res[i]);
        printf("{%lf, %lf}, ", i * (5.0 / 300), res2[i].x);
    }
    printf("\n");
    for (size_t i = 0; i < 301; i++) {
        //printf("%lf %lf\n", 1.0 + i * (5.0 / 30), res[i]);
        printf("{%lf, %lf}, ", i * (5.0 / 300), res2[i].y);
    }
    return 0;
}
