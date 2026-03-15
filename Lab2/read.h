#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* data;
    double key;
} Data;

Data* initiate_data(char* data, double key) {
    Data* dt = (Data*)malloc(sizeof(Data));
    dt->data = (char*)malloc(strlen(data) + 1);
    strcpy(dt->data, data);
    dt->key = key;
    return dt;
}

void free_data(Data* dt) {
    if (dt) {
        free(dt->data);
        free(dt);
    }
}

void free_data_array(Data** arr, int count) {
    for (int i = 0; i < count; ++i) {
        free_data(arr[i]);
    }
    free(arr);
}

Data** read(char* path) {
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("Can not open file\n");
        return NULL;
    }

    char str_count[12];
    fgets(str_count, sizeof(str_count), fp);
    
    int count = (int)strtod(str_count, NULL);
    printf("Count: %d\n", count);

    Data** main_massive = (Data**)malloc(count * sizeof(Data*));

    for (int i = 0; i < count; ++i) {
        char* line = NULL;
        size_t len = 0;
        
        getline(&line, &len, fp);
        double key = strtod(line, NULL);
        free(line);
        
        line = NULL;
        len = 0;
        getline(&line, &len, fp);
        
        Data* temp = initiate_data(line, key);
        main_massive[i] = temp;
        free(line);
    }

    fclose(fp);
    return main_massive;
}

Data*** collect_all_arrays() {
    Data*** arrays = (Data***)malloc(3 * sizeof(Data**));

    arrays[0] = read("test_data/test_sorted.txt");
    arrays[1] = read("test_data/test_reverse.txt");
    arrays[2] = read("test_data/test_random.txt");

    return arrays;
}

#endif
