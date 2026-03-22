#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include "rpn.h"
#include "rpn_to_tree.h"
#include "tree.h"
#define MAX_LENGHS  256



// opers priority:
// '+' || '-': 1
// '*' || '/': 2
// '^': 3


int main() {

    char str[MAX_LENGHS] = "(12+23-1)*20*1";

    if (validation(str)) {
        char* validated_str = str;
        char* rp = rpn(validated_str);
        if (rp == NULL) {
            printf("Memory allocation error\n");
            return 1;
        }
        printf("RPN: %s\n", rp);
        
        Node* tree = rpn_to_tree(rp);
        if (tree == NULL) {
            printf("Failed to build tree\n");
            free(rp);
            return 1;
        }
        
        printf("\nДерево до упрощения:");
        print_tree(tree);
        
        tree = remove_unit_factors_tree(tree);
        
        printf("\nДерево после упрощения:");
        print_tree(tree);
        
        free(rp);
    } else {
        printf("String is not valid\n");
        return 0;
    }

    




}