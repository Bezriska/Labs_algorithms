#include <stdio.h>
#include "read.h"

//Number of method: 7
//Structure: 5

int main() {
    Data** main_massive = read("test_data/test_sorted.txt");
    int count = read_count("test_data/test_sorted.txt");
    show(main_massive, count);
}


