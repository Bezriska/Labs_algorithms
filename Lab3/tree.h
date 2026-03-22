#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    int depth;
} Node;

Node* initiate_tree(int head_data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = head_data;
    n->left = NULL;
    n->right = NULL;
    n->depth = 0;
    return n;
}


void count_depth(Node* head, int* max_depth) {
    if (head->depth > *max_depth) {
        *max_depth = head->depth;
    }
    if (head->left != NULL) {
        count_depth(head->left, max_depth);
    }
    if (head->right != NULL) {
        count_depth(head->right, max_depth);
    }
}


int check_depth(Node* head) {
    int max_depth = 0;
    count_depth(head, &max_depth);
    return max_depth;
}


void print_tree_recursive(Node* node, int space) {
    if (node == NULL) return;
    
    space += 5;
    
    print_tree_recursive(node->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%c\n", node->data);
    
    print_tree_recursive(node->left, space);
}

void print_tree(Node* head) {
    printf("\n=== Дерево ===\n");
    print_tree_recursive(head, 0);
    printf("==============\n\n");
}

int is_leaf(Node* node) {
    return (node != NULL && node->left == NULL && node->right == NULL);
}

int is_operator(Node* node) {
    if (node == NULL) return 0;
    char c = (char)node->data;
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Node* remove_unit_factors_tree(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    
    node->left = remove_unit_factors_tree(node->left);
    node->right = remove_unit_factors_tree(node->right);

    if (node->data == '*') {
        if (is_leaf(node->left) && node->left->data == '1') {
            Node* temp = node->right;
            free(node->left);
            free(node);
            return temp;
        }
        
        // Случай 2: правый операнд — листовая 1
        if (is_leaf(node->right) && node->right->data == '1') {
            Node* temp = node->left;
            free(node->right);
            free(node);
            return temp;
        }
    }
    
    return node;
}

#endif