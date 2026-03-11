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

void show(Data** main_massive, int count) {
    for (int i = 0; i < count; ++i) {
        printf("\nElement %d\n", i);
        printf("Key: %lf\n", main_massive[i]->key);
        printf("Data: %s\n", main_massive[i]->data);
    }
}
