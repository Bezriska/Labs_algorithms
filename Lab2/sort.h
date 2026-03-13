#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include "read.h"
#include "help.h"


void shell_sort(Data** array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j]->key > array[j + s]->key; j -= s) {
                Data* temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}

void sort_all_data(Data*** data_arrs, int* count_arrs) {
    for (int i = 0; i < 3; ++i) {
        printf("\nShell sort:\n");

        printf("\nSource array number %d: \n", i);
        show(data_arrs[i], count_arrs[i]);
        
        printf("\nArr number %d sorts...\n", i);
        shell_sort(data_arrs[i], count_arrs[i]);

        printf("Sorted array number %d:\n", i);
        show(data_arrs[i], count_arrs[i]);
    }   
}







#endif