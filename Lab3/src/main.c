#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include "rpn.h"
#include "rpn_to_tree.h"
#include "tree.h"
#include "calculate_tree.h"
#include "read_expr.h"



// opers priority:
// '+' || '-': 1
// '*' || '/': 2
// '^': 3


int main() {

    
    printf("Введите выражение: ");
    char* str = read_expr();


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
        
        printf("Итеративное упрощение\n");
        for (int i = 0; i < 3; i++) {
            tree = simplify(tree);
            tree = remove_unit_factors_tree(tree);
        }
        
        printf("\nДерево после максимального упрощения:");
        print_tree(tree);
        
        free(rp);
    } else {
        printf("String is not valid\n");
        return 0;
    }


    




}