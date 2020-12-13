#include <stdio.h>

#include "RK.h"
#include "boundary.h"

extern F2 functions_single[];
extern F3 functions_double[][2];
extern F1 functions_coefs[][3];

int main(void) {
    unsigned mode;
    scanf("%u", &mode);

    if (mode == 0) {
        unsigned equations_cnt, order;
        scanf("%u%u", &equations_cnt, &order);
        if (equations_cnt != 1 && equations_cnt != 2) {
            fprintf(stderr, "Поддерживается решение одного ОДУ или системы двух ОДУ\n");
            return 2;
        }
        if (order != 2 && order != 4) {
            fprintf(stderr, "Поддерживается метод Рунге-Кутты 2 и 4 порядка\n");
            return 2;
        }
        if (equations_cnt == 1) {
            // Считываются начальные условия, длина отрезка на котором будет построена сетка, количество узлов
            // и номер функции для вычислений
            data_t x_0, y_0, len;
            unsigned n_steps, n;
            if (scanf("%lf%lf%lf%u%u", &x_0, &y_0, &len, &n, &n_steps) != 5) {
                fprintf(stderr, "Некоректные параметры вычислений");
                return 2;
            }
            data_t *res = rk_single(functions_single[n - 1], order == 2 ? RK_2 : RK_4, x_0, y_0, len, n_steps);
            if (res == NULL) {
                fprintf(stderr, "Ошибка времени выполнения\n");
                return 1;
            }
            for (size_t i = 0; i < n_steps + 1; i++) {
                printf("%lf %lf\n", x_0 + i * (len / n_steps), res[i]);
            }
        } else {
            // Считываются начальные условия, длина отрезка на котором будет построена сетка, количество узлов
            // и номер функции для вычислений
            data_t t_0, x_0, y_0, len;
            unsigned n_steps, n;
            if (scanf("%lf%lf%lf%lf%u%u", &t_0, &x_0, &y_0, &len, &n, &n_steps) != 5) {
                fprintf(stderr, "Некоректные параметры вычислений");
                return 2;
            }

            Vector2D *res = rk_double(functions_double[n][0], functions_double[n][1], order == 2 ? RK_2 : RK_4,
                                      t_0, x_0, y_0, len, n_steps);
            if (res == NULL) {
                fprintf(stderr, "Ошибка времени выполнения\n");
                return 1;
            }

            for (size_t i = 0; i < n_steps + 1; i++) {
                printf("{%lf, %lf}, ", t_0 + i * (len / n_steps), res[i].x);
            }
            printf("\n");
            for (size_t i = 0; i < n_steps + 1; i++) {
                printf("{%lf, %lf}, ", t_0 + i * (len / n_steps), res[i].y);
            }
        }
    } else {
        data_t x_0, x_n;
        unsigned n_steps, function_set;
        Vector2D init[3];
        scanf("%u%lf%lf%lf%lf%lf%lf%lf%lf%u", &function_set, &x_0, &x_n, &init[0].x, &init[1].x, &init[2].x,
              &init[0].y, &init[1].y, &init[2].y, &n_steps);
        data_t *res = boundary(x_0, x_n, functions_coefs[function_set - 1], init, n_steps);

        for (size_t i = 0; i < n_steps + 1; i++) {
            printf("%lf %lf\n", x_0 + (x_n - x_0) / n_steps * i, res[i]);
        }
    }
    return 0;
}
