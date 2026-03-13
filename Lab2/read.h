#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char data[256];
    double key;
} Data;

Data* initiate_data(char* data, double key) {
    Data* dt = (Data*)malloc(sizeof(Data));
    strncpy(dt->data, data, sizeof(dt->data) - 1);
    dt->data[sizeof(dt->data) - 1] = '\0';
    dt->key = key;
    return dt;
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
        char buffer[128];
        fgets(buffer, sizeof(buffer), fp);
        double key = strtod(buffer, NULL);
        
        char data_buffer[128];
        fgets(data_buffer, sizeof(data_buffer), fp);
        
        Data* temp = initiate_data(data_buffer, key);
        main_massive[i] = temp;
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

#endif // READ_H
