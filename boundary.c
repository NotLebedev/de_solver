#include <stdlib.h>
#include "boundary.h"

double *boundary(double x_0, double x_n, f1 eq_coef[3], Vector2D init_coef[3], size_t n) {
    double *res = NULL, *alpha = NULL, *beta = NULL;
    res = calloc(n + 1, sizeof(*res));
    alpha = calloc(n, sizeof(*alpha));
    beta = calloc(n, sizeof(*beta));
    if (res == NULL || alpha == NULL || beta == NULL) {
        goto error;
    }

    double step = (x_n - x_0) / n;

    // Вычисляем коэффициенты для метода прогонки
    alpha[0] = -init_coef[1].x / (init_coef[0].x * step - init_coef[1].x);
    beta[0] = init_coef[2].x / (init_coef[0].x - init_coef[1].x / step);

    for (size_t i = 1; i < n; i++) {
        // Вычисляем элементы матрицы в i строке
        double C = 1.0 / (step * step) - eq_coef[0](x_0 + i * step) / (2 * step);
        double A = 1.0 / (step * step) + eq_coef[0](x_0 + i * step) / (2 * step);
        double B = -2.0 / (step * step) + eq_coef[1](x_0 + i * step);
        double F = eq_coef[2](x_0 + i * step);

        // По общей формуле вычисляем кожффициенты метода прогонки
        alpha[i] = -C / (A * alpha[i - 1] + B);
        beta[i] = (F - beta[i-1] * A) / (A * alpha[i - 1] + B);
    }

    res[n] = (init_coef[2].y * step + init_coef[1].y * beta[n - 1]) / (init_coef[0].y * step +
            init_coef[1].y - init_coef[1].y * alpha[n-1]);
    for (ssize_t i = n - 1; i >= 0; i++) {
        res[i] = alpha[i] * res[i + 1] + beta[i];
    }

    return res;
error:
    free(res);
    free(alpha);
    free(beta);
    return NULL;
}
