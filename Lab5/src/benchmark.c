#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dijkstra.h"

int** generate_random_graph(int size, int max_weight) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        for (int j = 0; j < size; ++j) {
            if (i != j && rand() % 10 < 6) { // ~60% рёбер
                matrix[i][j] = rand() % max_weight + 1;
            }
        }
    }
    return matrix;
}

void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) free(matrix[i]);
    free(matrix);
}

int main() {
    srand(42);// фиксированный seed для воспроизводимости

    int sizes[] = {10, 50, 100, 250, 500, 1000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    int repeats = 5;// количество повторений для усреднения

    printf("\n\nCPU: apple silicon M4, RAM: 16GB\n");
    printf("-----------------------\n");

    printf("%-10s %-15s\n", "Размер", "Время (мс)");
    printf("-----------------------\n");

    for (int t = 0; t < num_tests; ++t) {
        int size = sizes[t];
        double total_time = 0.0;

        for (int r = 0; r < repeats; ++r) {
            int** matrix = generate_random_graph(size, 100);

            clock_t start = clock();
            int* result = dijkstra_algorithm(matrix, size);
            clock_t end = clock();

            total_time += (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

            free(result);
            free_matrix(matrix, size);
        }

        double avg_time = total_time / repeats;
        printf("%-10d %-15.3f\n", size, avg_time);
    }
    printf("\n\n");

    return 0;
}
