#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include "read.h"
#include "help.h"
#include "sort.h"

Data* binary_search(Data** array, int count, double search_key) {
    int left = 0;
    int right = count - 1; 
    
    while (left <= right) {
        int mid = (left+right)/2;

        if (array[mid]->key == search_key) {
            return array[mid];
        }

        if (array[mid]->key < search_key) {
            left = mid + 1;
        } else if (array[mid]->key > search_key) {
            right = mid - 1;
        }
    }

    return NULL;
}







#endif