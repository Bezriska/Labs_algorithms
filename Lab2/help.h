#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include "read.h"

void show(Data** main_massive, int count) {
    for (int i = 0; i < count; ++i) {
        printf("\nElement %d\n", i);
        printf("Key: %lf\n", main_massive[i]->key);
        printf("Data: %s\n", main_massive[i]->data);
    }
}

int read_count(char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("Can not open file\n");
        return 0;
    }
    
    char str_count[12];
    fgets(str_count, sizeof(str_count), fp);
    
    int count = (int)strtod(str_count, NULL);
    fclose(fp);
    return count;
}

int* read_count_in_arr() {
    int* count_arr = (int*)malloc(3 * sizeof(int));

    count_arr[0] = read_count("test_data/test_sorted.txt");
    count_arr[1] = read_count("test_data/test_reverse.txt");
    count_arr[2] = read_count("test_data/test_random.txt");
    
    return count_arr;
}

#endif // HELP_H
