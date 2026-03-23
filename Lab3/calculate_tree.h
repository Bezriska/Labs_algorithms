#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "tree.h"

int is_variable(Node* node) {
    return (node != NULL && node->type == NODE_VARIABLE);
}

int is_number_node(Node* node) {
    return (node != NULL && node->type == NODE_NUMBER);
}

Node* simplify(Node* top) {
    if (top == NULL) return NULL;

    top->left = simplify(top->left);
    top->right = simplify(top->right);

    if (is_leaf(top->left) && is_leaf(top->right) && 
        is_number_node(top->left) && is_number_node(top->right)) {
        
        int left = top->left->value.number;
        int right = top->right->value.number;
        char op = top->value.op;
        
        if (op == '+') {
            top->type = NODE_NUMBER;
            top->value.number = left + right;
        } else if (op == '-') {
            top->type = NODE_NUMBER;
            top->value.number = left - right;
        } else if (op == '*') {
            top->type = NODE_NUMBER;
            top->value.number = left * right;
        } else if (op == '/') {
            if (right == 0) {
                printf("Error: Division by zero\n");
                return top;
            }
            top->type = NODE_NUMBER;
            top->value.number = left / right;
        } else if (op == '^') {
            top->type = NODE_NUMBER;
            top->value.number = (int)pow(left, right);
        }
        
        free(top->left);
        free(top->right);
        top->left = NULL;
        top->right = NULL;
    }

    return top;

}








#endif