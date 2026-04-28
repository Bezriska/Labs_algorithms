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

int* generate_sizes(int max_size, int* count) {
    int temp_count = 0;
    
    for (int i = 0; i <= max_size; i += 50) ++temp_count;
    int* numbers = (int*)malloc(temp_count * sizeof(int));
    for (int i = 0, val = 0; val <= max_size; val += 50, ++i) {
        numbers[i] = val;
    }
    *count = temp_count;
    return numbers;
}

int main() {
    srand(42);// фиксированный seed для воспроизводимости

    int count = 0;
    int* sizes = generate_sizes(1000, &count);
    int num_tests = count;
    int repeats = 5;// количество повторений для усреднения

    printf("\n\nCPU: apple silicon M4, RAM: 16GB\n");
    printf("-----------------------\n");

    printf("%-10s %-15s\n", "Размер", "Время (мс)");
    printf("-----------------------\n");

    FILE* fp = fopen("../DATA/benchmark.txt", "w");
    if (!fp) {
        printf("Невозможно открыть файл с бенчмарками\n");
        return 1;
    }

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
        fprintf(fp, "%d  %.3f\n", size, avg_time);
    }
    printf("\n\n");

    fclose(fp);
    return 0;
}
