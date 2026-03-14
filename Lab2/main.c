#include <stdio.h>
#include "read.h"
#include "help.h"
#include "sort.h"
#include "search.h"

//Number of method: 7
//Structure: 5

int main() {
    Data*** arrays = collect_all_arrays();

    printf("All arrays are successfully collected");
    int* count_arr = read_count_in_arr();
    sort_all_data(arrays, count_arr);

    printf("\nChoose array for binary search:\n1) Sorted array\n2) Reverse array\n3)Random array\n");
    int num_arr;

    Data** choosed_array;
    int count;


    label:
    scanf("%d", &num_arr);
    switch (num_arr) {
        case 1:
            choosed_array = arrays[0];
            count = count_arr[0];
            break;

        case 2:
            choosed_array = arrays[1];
            count = count_arr[1];
            break;

        case 3:
            choosed_array = arrays[2];
            count = count_arr[2];
            break;

        default:
            printf("Choose number in range 1-3\n");
            goto label;
    }

    while (1) {
        double key;
        printf("\nPrint key: (print -1 to exit)\n");
        scanf("%lf", &key);
        
        if (key == -1) {
            return 1;
        }

        Data* ret_structure;
        ret_structure = binary_search(choosed_array, count, key);
        if (ret_structure != NULL) {
            printf("Data: %s", ret_structure->data);
        } else {
            printf("Data not found");
        }

    }
}


