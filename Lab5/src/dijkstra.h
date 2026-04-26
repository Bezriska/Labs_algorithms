#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <limits.h>
#include <stdlib.h>
#include <string.h>





int check_if_in_checked(int peak, int* checked, int size) {
    for (int i = 0; i < size; ++i) {
        if (peak != checked[i]) {
            continue;
        } else {
            return 1;
        }
    }
    return 0;
}

int min_num(int* out, int* checked, int size) {
    int result = -1;
    int min_val = INT_MAX;
    for (int i = 0; i < size; ++i) {
        if (out[i] < min_val && !check_if_in_checked(i, checked, size)) {
            min_val = out[i];
            result = i;
        }
    }
    return result;
}

int* dijkstra_algorithm(int** matrix, int size) {
    int inf = INT_MAX;
    int* out = (int*)malloc(size * sizeof(int));
    for (int j = 0; j < size; ++j) {
        out[j] = inf;
    }

    int start = 0;
    out[start] = 0; // расстояние до стартовой вершины = 0

    int* checked = (int*)malloc(size * sizeof(int));
    memset(checked, -1, size * sizeof(int)); // инициализируем -1 (нет вершины)
    int checked_count = 0;
    checked[checked_count++] = start;

    while (start != -1) {
        // итерируемся по соседям (i — индекс вершины)
        for (int i = 0; i < size; ++i) {
            if (matrix[start][i] > 0 && !check_if_in_checked(i, checked, checked_count)) {
                int w = out[start] + matrix[start][i];
                if (w < out[i]) {
                    out[i] = w;
                }
            }
        }
        start = min_num(out, checked, size);
        if (start != -1) {
            checked[checked_count++] = start;
        }
    }

    return out;
}










#endif