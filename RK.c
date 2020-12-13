#include <stdlib.h>

#include "RK.h"

data_t *rk_single(F2 func, Order order, data_t x0, data_t y0, data_t l, size_t n) {
    // Создаём массив, содержащий значения по x для равномерной сетки от x0 до x0 + l с шагом l/n
    data_t *res = calloc(n + 1, sizeof(*res));
    if (res == NULL) {
        return NULL;
    }

    // Задаём начальное значение
    res[0] = y0;
    // Задаём шаг сетки алгоритма
    const data_t step = l / n;
    for (size_t i = 0; i < n; i++) {
        const data_t x_prev = x0 + i * step;
        const data_t y_prev = res[i];

        // Представим результат в новом узле в виде y_i+1 = y_i + variation, variation вычислим в зависимости от
        // выбранного порядка
        data_t variation;
        if (order == RK_2) {
            const data_t k1 = func(x_prev, y_prev);
            const data_t k2 = func(x_prev + step, y_prev + step * k1);
            variation = (k1 + k2) * step / 2.0;
        } else {
            const data_t k1 = func(x_prev, y_prev);
            const data_t k2 = func(x_prev + step / 2.0, y_prev + step * k1 / 2.0);
            const data_t k3 = func(x_prev + step / 2.0, y_prev + step * k2 / 2.0);
            const data_t k4 = func(x_prev + step, y_prev + step * k3);
            variation = (k1 + 2.0 * k2 + 2.0 * k3 + k4) * step / 6.0;
        }

        res[i + 1] = y_prev + variation;
    }
    return res;
}

Vector2D *rk_double(F3 func1, F3 func2, Order order, data_t t0, data_t x0, data_t y0, data_t l, size_t n) {
    Vector2D *res = calloc(n + 1, sizeof(*res));
    if (res == NULL) {
        return NULL;
    }

    // Задаём начальное значение
    res[0].x = x0;
    res[0].y = y0;

    // Задаём шаг сетки алгоритма
    const data_t step = l / n;
    for (size_t i = 0; i < n; i++) {
        const data_t t_prev = t0 + i * step;
        const data_t x_prev = res[i].x;
        const data_t y_prev = res[i].y;

        // Представим результат в новом узле в виде x_{i+1} = x_i + variation_x, variation_x вычислим в зависимости от
        // выбранного порядка и аналогично для y
        data_t variation_x;
        data_t variation_y;
        if (order == RK_2) {
            const data_t k1 = func1(t_prev, x_prev, y_prev);
            const data_t l1 = func2(t_prev, x_prev, y_prev);
            const data_t k2 = func1(t_prev + step, x_prev + step * k1, y_prev + step * l1);
            const data_t l2 = func2(t_prev + step, x_prev + step * k1, y_prev + step * l1);
            variation_x = (k1 + k2) * step / 2.0;
            variation_y = (l1 + l2) * step / 2.0;
        } else {
            const data_t k1 = func1(t_prev, x_prev, y_prev);
            const data_t l1 = func2(t_prev, x_prev, y_prev);

            const data_t k2 = func1(t_prev + step / 2.0, x_prev + step * k1 / 2.0, y_prev + step * l1 / 2.0);
            const data_t l2 = func2(t_prev + step / 2.0, x_prev + step * k1 / 2.0, y_prev + step * l1 / 2.0);

            const data_t k3 = func1(t_prev + step / 2.0, x_prev + step * k2 / 2.0, y_prev + step * l2 / 2.0);
            const data_t l3 = func2(t_prev + step / 2.0, x_prev + step * k2 / 2.0, y_prev + step * l2 / 2.0);

            const data_t k4 = func1(t_prev + step, x_prev + step * k3, y_prev + step * l3);
            const data_t l4 = func2(t_prev + step, x_prev + step * k3, y_prev + step * l3);

            variation_x = (k1 + 2.0 * k2 + 2.0 * k3 + k4) * step / 6.0;
            variation_y = (l1 + 2.0 * l2 + 2.0 * l3 + l4) * step / 6.0;
        }

        res[i + 1].x = x_prev + variation_x;
        res[i + 1].y = y_prev + variation_y;
    }
    return res;
}
