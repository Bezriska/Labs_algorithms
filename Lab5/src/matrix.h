#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <stdio.h>

int** initiate_matrix(int size) {
    int **matrix = (int**)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

int take_element(int str, int column, int** matrix) {
    int i = str - 1;
    int j = column - 1;
    return matrix[i][j];
}

int** write_matrix_from_terminal(int size) {
    

    int** matrix = initiate_matrix(size);
    int element;

    printf("\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("Введите элемент %d строки, %d столбца: \n", i+1, j+1);
            scanf("%d", &element);
            if (element < 0) {
                while (1) {
                    printf("Элемент должен быть неотрицательным, попробуйте еще раз\n");
                    printf("Введите элемент %d строки, %d столбца: \n", i+1, j+1);
                    scanf("%d", &element);
                    if (element < 0) {
                        continue;
                    } else {
                        matrix[i][j] = element;
                        break;
                    }
                }
            } else {
                matrix[i][j] = element;
            }
        }
    }
    return matrix;
}

void print_matrix(int size, int** matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}















#endif