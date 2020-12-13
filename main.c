#include <stdio.h>
#include <stdlib.h>

#include "RK.h"

extern f2 functions_single[];
extern f3 functions_double[][2];

int main(int argc, char *argv[]) {
    unsigned mode = strtoull(argv[1], NULL, 0);

    if (mode == 0) {
        unsigned equations_cnt = strtoull(argv[2], NULL, 0);
        if (equations_cnt != 1 && equations_cnt != 2) {
            fprintf(stderr, "Поддерживается решение одного ОДУ или системы двух ОДУ\n");
            return 2;
        }

        unsigned order = strtoull(argv[3], NULL, 0);
        if (order != 2 && order != 4) {
            fprintf(stderr, "Поддерживается метод Рунге-Кутты 2 и 4 порядка\n");
            return 2;
        }
        if (equations_cnt == 1) {
            // Считываются начальные условия, длина отрезка на котором будет построена сетка, количество узлов
            // и номер функции для вычислений
            double x_0, y_0, len;
            unsigned n_steps, n;
            if (scanf("%lf%lf%lf%u%u", &x_0, &y_0, &len, &n_steps, &n) != 5) {
                fprintf(stderr, "Некоректные параметры вычислений");
                return 2;
            }
            double *res = rk_single(functions_single[n - 1], order == 2 ? RK_2 : RK_4, x_0, y_0, len, n_steps);
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
            double t_0, x_0, y_0, len;
            unsigned n_steps, n;
            if (scanf("%lf%lf%lf%lf%u%u", &t_0, &x_0, &y_0, &len, &n_steps, &n) != 5) {
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

    }
    return 0;
}
