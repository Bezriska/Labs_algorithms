// Смежность и Дейкстра
#include <stdio.h>
#include "matrix.h"
#include "dijkstra.h"


int main() {
    printf("Введите матрицу смежности:\n");
    int size;
    printf("Введите размерность матрицы: ");
    scanf("%d", &size);
    int** matrix = write_matrix_from_terminal(size);

    printf("\nВаша матрица:\n");
    print_matrix(size, matrix);
    printf("\n");

    int* res_dij = dijkstra_algorithm(matrix, size);
    printf("Результат работы алгоритма Дейкстры:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", res_dij[i]);
    }
    printf("\n");

    free_matrix(matrix, size);

}