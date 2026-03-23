#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>

// Тип узла
typedef enum {
    NODE_NUMBER,
    NODE_OPERATOR,
    NODE_VARIABLE
} NodeType;

typedef struct node {
    NodeType type;
    union {
        int number;
        char op;
        char variable;
    } value;
    struct node* left;
    struct node* right;
    int depth;
} Node;

Node* initiate_tree(int head_data) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (head_data >= 32 && head_data <= 126) {
        char c = (char)head_data;
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') {
            n->type = NODE_OPERATOR;
            n->value.op = c;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            n->type = NODE_VARIABLE;
            n->value.variable = c;
        } else {
            n->type = NODE_NUMBER;
            n->value.number = head_data;
        }
    } else {
        n->type = NODE_NUMBER;
        n->value.number = head_data;
    }
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
    
    switch (node->type) {
        case NODE_NUMBER:
            printf("%d\n", node->value.number);
            break;
        case NODE_OPERATOR:
            printf("%c\n", node->value.op);
            break;
        case NODE_VARIABLE:
            printf("%c\n", node->value.variable);
            break;
    }
    
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
    return (node != NULL && node->type == NODE_OPERATOR);
}

Node* remove_unit_factors_tree(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    
    node->left = remove_unit_factors_tree(node->left);
    node->right = remove_unit_factors_tree(node->right);

    if (node->type == NODE_OPERATOR && node->value.op == '*') {
        if (is_leaf(node->left) && node->left->type == NODE_NUMBER && node->left->value.number == 1) {
            Node* temp = node->right;
            free(node->left);
            free(node);
            return temp;
        }
        
        if (is_leaf(node->right) && node->right->type == NODE_NUMBER && node->right->value.number == 1) {
            Node* temp = node->left;
            free(node->right);
            free(node);
            return temp;
        }
    }
    
    return node;
}

int child_exist(Node* top) {
    if (top->left && top->right) return 1;
    else return 0;
}

#endif