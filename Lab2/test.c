#include <stdio.h>
#include "read.h"
#include "help.h"
#include "sort.h"
#include "search.h"
#include <assert.h>
#include <string.h>

void test_initiate_data() {
    printf("Testing initiate_data...\n");
    
    Data* data = initiate_data("Test string", 3.14);
    
    assert(data != NULL);
    assert(strcmp(data->data, "Test string") == 0);
    assert(data->key == 3.14);
    
    free(data);
    printf("test_initiate_data passed\n");
}

void test_shell_sort() {
    printf("Testing shell_sort...\n");
    
    Data** array = (Data**)malloc(5 * sizeof(Data*));
    array[0] = initiate_data("Five", 5.0);
    array[1] = initiate_data("Two", 2.0);
    array[2] = initiate_data("Four", 4.0);
    array[3] = initiate_data("One", 1.0);
    array[4] = initiate_data("Three", 3.0);
    
    shell_sort(array, 5);
    
    assert(array[0]->key == 1.0);
    assert(array[1]->key == 2.0);
    assert(array[2]->key == 3.0);
    assert(array[3]->key == 4.0);
    assert(array[4]->key == 5.0);
    
    assert(strcmp(array[0]->data, "One") == 0);
    assert(strcmp(array[1]->data, "Two") == 0);
    assert(strcmp(array[2]->data, "Three") == 0);
    assert(strcmp(array[3]->data, "Four") == 0);
    assert(strcmp(array[4]->data, "Five") == 0);
    
    for (int i = 0; i < 5; i++) {
        free(array[i]);
    }
    free(array);
    
    printf("test_shell_sort passed\n");
}

void test_binary_search() {
    printf("Testing binary_search...\n");
    
    Data** array = (Data**)malloc(5 * sizeof(Data*));
    array[0] = initiate_data("One", 1.0);
    array[1] = initiate_data("Two", 2.0);
    array[2] = initiate_data("Three", 3.0);
    array[3] = initiate_data("Four", 4.0);
    array[4] = initiate_data("Five", 5.0);
    
    Data* result = binary_search(array, 5, 3.0);
    assert(result != NULL);
    assert(result->key == 3.0);
    assert(strcmp(result->data, "Three") == 0);
    
    result = binary_search(array, 5, 1.0);
    assert(result != NULL);
    assert(result->key == 1.0);
    
    result = binary_search(array, 5, 5.0);
    assert(result != NULL);
    assert(result->key == 5.0);
    
    result = binary_search(array, 5, 6.0);
    assert(result == NULL);
    
    result = binary_search(array, 5, 0.5);
    assert(result == NULL);
    
    for (int i = 0; i < 5; i++) {
        free(array[i]);
    }
    free(array);
    
    printf("test_binary_search passed\n");
}

void test_shell_sort_empty() {
    printf("Testing shell_sort with edge cases...\n");
    
    Data** array = (Data**)malloc(1 * sizeof(Data*));
    array[0] = initiate_data("Single", 1.0);
    
    shell_sort(array, 1);
    assert(array[0]->key == 1.0);
    
    free(array[0]);
    free(array);
    
    array = (Data**)malloc(3 * sizeof(Data*));
    array[0] = initiate_data("A", 1.0);
    array[1] = initiate_data("B", 2.0);
    array[2] = initiate_data("C", 3.0);
    
    shell_sort(array, 3);
    assert(array[0]->key == 1.0);
    assert(array[1]->key == 2.0);
    assert(array[2]->key == 3.0);
    
    for (int i = 0; i < 3; i++) {
        free(array[i]);
    }
    free(array);
    
    printf("test_shell_sort edge cases passed\n");
}

int main() {
    printf("=== Running Tests ===\n\n");
    
    test_initiate_data();
    test_shell_sort();
    test_shell_sort_empty();
    test_binary_search();
    
    printf("\n=== All Tests Passed! ===\n");
    return 0;
}