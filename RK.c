#include <stddef.h>
#include <stdlib.h>

#include "RK.h"

double *rk_single(f2 func, Order order, double x0, double y0, double l, size_t n) {
    // Создаём массив, содержащий значения по y для равномерной сетки от x0 до x0 + l с шагом l/n
    double *res = calloc(n + 1, sizeof(*res));
    if (res == NULL) {
        return NULL;
    }

    // Задаём начальное значение
    res[0] = y0;
    // Задаём шаг сетки алгоритма
    const double step = l / n;
    for (size_t i = 0; i < n; i++) {
        const double x_prev = x0 + i * step;
        const double y_prev = res[i];

        // Представим результат в новом узле в виде y_i+1 = y_i + variation, variation вычислим в зависимости от
        // выбранного порядка
        double variation;
        if (order == RK_2) {
            const double k1 = func(x_prev, y_prev);
            const double k2 = func(x_prev + step, y_prev + step * k1);
            variation = (k1 + k2) * step / 2.0;
        } else {
            const double k1 = func(x_prev, y_prev);
            const double k2 = func(x_prev + step / 2.0, y_prev + step * k1 / 2.0);
            const double k3 = func(x_prev + step / 2.0, y_prev + step * k2 / 2.0);
            const double k4 = func(x_prev + step, y_prev + step * k3);
            variation = (k1 + 2.0 * k2 + 2.0 * k3 + k4) * step / 6.0;
        }

        res[i + 1] = y_prev + variation;
    }
    return res;
}
