#include <stddef.h>
#include <stdlib.h>

#include "RK.h"

double *rk_single(f2 func, Order order, double x0, double y0, double l, size_t n) {
    // Создаём массив, содержащий значения по x для равномерной сетки от x0 до x0 + l с шагом l/n
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

Vector2D *rk_double(f3 func1, f3 func2, Order order, double t0, double x0, double y0, double l, size_t n) {
    Vector2D *res = calloc(n + 1, sizeof(*res));
    if (res == NULL) {
        return NULL;
    }

    // Задаём начальное значение
    res[0].x = x0;
    res[0].y = y0;

    // Задаём шаг сетки алгоритма
    const double step = l / n;
    for (size_t i = 0; i < n; i++) {
        const double t_prev = t0 + i * step;
        const double x_prev = res[i].x;
        const double y_prev = res[i].y;

        // Представим результат в новом узле в виде x_{i+1} = x_i + variation_x, variation_x вычислим в зависимости от
        // выбранного порядка и аналогично для y
        double variation_x;
        double variation_y;
        if (order == RK_2) {
            const double k1 = func1(t_prev, x_prev, y_prev);
            const double l1 = func2(t_prev, x_prev, y_prev);
            const double k2 = func1(t_prev + step, x_prev + step * k1, y_prev + step * l1);
            const double l2 = func2(t_prev + step, x_prev + step * k1, y_prev + step * l1);
            variation_x = (k1 + k2) * step / 2.0;
            variation_y = (l1 + l2) * step / 2.0;
        } else {
            const double k1 = func1(t_prev, x_prev, y_prev);
            const double l1 = func2(t_prev, x_prev, y_prev);

            const double k2 = func1(t_prev + step / 2.0, x_prev + step * k1 / 2.0, y_prev + step * l1 / 2.0);
            const double l2 = func2(t_prev + step / 2.0, x_prev + step * k1 / 2.0, y_prev + step * l1 / 2.0);

            const double k3 = func1(t_prev + step / 2.0, x_prev + step * k2 / 2.0, y_prev + step * l2 / 2.0);
            const double l3 = func2(t_prev + step / 2.0, x_prev + step * k2 / 2.0, y_prev + step * l2 / 2.0);

            const double k4 = func1(t_prev + step, x_prev + step * k3, y_prev + step * l3);
            const double l4 = func2(t_prev + step, x_prev + step * k3, y_prev + step * l3);

            variation_x = (k1 + 2.0 * k2 + 2.0 * k3 + k4) * step / 6.0;
            variation_y = (l1 + 2.0 * l2 + 2.0 * l3 + l4) * step / 6.0;
        }

        res[i + 1].x = x_prev + variation_x;
        res[i + 1].y = y_prev + variation_y;
    }
    return res;
}
