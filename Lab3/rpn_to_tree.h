#ifndef TREE_TO_RPN_H
#define TREE_TO_RPN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rpn.h"
#include "tree.h"


int is_number(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

Node* rpn_to_tree(char* str_rpn) {
    if (str_rpn == NULL || strlen(str_rpn) == 0) {
        return NULL;
    }
    
    Node** stack = (Node**)malloc(strlen(str_rpn) * sizeof(Node*));
    int stack_size = 0;
    
    char* temp = strdup(str_rpn);
    char* token = strtok(temp, " ");
    
    while (token != NULL) {
        if (is_number(token)) {
            Node* node = initiate_tree(token[0]);
            stack[stack_size++] = node;
        } 
        else if (isoper(token[0]) && strlen(token) == 1) {
            if (stack_size < 2) {
                free(temp);
                free(stack);
                return NULL;
            }
            
            Node* right = stack[--stack_size];
            Node* left = stack[--stack_size];
            
            Node* op_node = initiate_tree(token[0]);
            op_node->left = left;
            op_node->right = right;
            
            int left_depth = (left != NULL) ? left->depth : -1;
            int right_depth = (right != NULL) ? right->depth : -1;
            op_node->depth = (left_depth > right_depth ? left_depth : right_depth) + 1;
            
            stack[stack_size++] = op_node;
        }
        
        token = strtok(NULL, " ");
    }
    
    free(temp);
    
    if (stack_size != 1) {
        free(stack);
        return NULL;
    }
    
    Node* root = stack[0];
    free(stack);
    
    return root;
}


#endif