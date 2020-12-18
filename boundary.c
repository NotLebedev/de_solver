#include <stdlib.h>
#include "boundary.h"

data_t *boundary(data_t x_0, data_t x_n, F1 eq_coef[3], Vector2D init_coef[3], size_t n) {
    data_t *res = NULL, *alpha = NULL, *beta = NULL;
    res = calloc(n + 1, sizeof(*res));
    alpha = calloc(n, sizeof(*alpha));
    beta = calloc(n, sizeof(*beta));
    if (res == NULL || alpha == NULL || beta == NULL) {
        goto error;
    }

    data_t step = (x_n - x_0) / n;

    // Вычисляем коэффициенты для метода прогонки
    alpha[0] = -init_coef[1].x / (init_coef[0].x * step - init_coef[1].x);
    beta[0] = init_coef[2].x / (init_coef[0].x - init_coef[1].x / step);

    for (size_t i = 1; i < n; i++) {
        // Вычисляем элементы матрицы в i строке
        data_t A = 1.0 / (step * step) - eq_coef[0](x_0 + i * step) / (2 * step);
        data_t B = -2.0 / (step * step) + eq_coef[1](x_0 + i * step);
        data_t C = 1.0 / (step * step) + eq_coef[0](x_0 + i * step) / (2 * step);
        data_t F = eq_coef[2](x_0 + i * step);

        // По общей формуле вычисляем коэффициенты метода прогонки
        alpha[i] = -C / (A * alpha[i - 1] + B);
        beta[i] = (F - beta[i - 1] * A) / (A * alpha[i - 1] + B);
    }

    res[n] = (init_coef[2].y * step + init_coef[1].y * beta[n - 1]) / (init_coef[0].y * step +
                                                                       init_coef[1].y - init_coef[1].y * alpha[n - 1]);
    for (ssize_t i = n - 1; i >= 0; i--) {
        res[i] = alpha[i] * res[i + 1] + beta[i];
    }

    free(alpha);
    free(beta);
    return res;
    error:
    free(res);
    free(alpha);
    free(beta);
    return NULL;
}
