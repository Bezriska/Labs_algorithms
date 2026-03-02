#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    int depth;
} Node;

Node* initiate_tree(int head_data) {
    Node* n = malloc(sizeof(Node));
    n->data = head_data;
    n->left = NULL;
    n->right = NULL;
    n->depth = 0;
    return n;
}

void add(int data, Node* head) {

    while (1) {
        
        if (data < head->data) {
            if (head->left) {
                head = head->left;
            }
            else {
                Node* n = malloc(sizeof(Node));
                n->data = data;
                n->left = NULL;
                n->right = NULL;
                n->depth = head->depth + 1;
                head->left = n;
                break;
            }

        } else if (data > head->data) {
            if (head->right) {
                head = head->right;
            }
            else {
                Node* n = malloc(sizeof(Node));
                n->data = data;
                n->left = NULL;
                n->right = NULL;
                n->depth = head->depth + 1;
                head->right = n;
                break;
            }
        }
    }
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

int child_exist(Node* head) {
    if (head->left && head->right) return 1;
    else return 0;
}

void print_tree_recursive(Node* node, int space) {
    if (node == NULL) return;
    
    space += 5;
    
    print_tree_recursive(node->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);
    
    print_tree_recursive(node->left, space);
}

void print_tree(Node* head) {
    printf("\n=== Дерево ===\n");
    print_tree_recursive(head, 0);
    printf("==============\n\n");
}

Node* delete(int data, Node* head) {
    if (!head) return NULL;

    if (data < head->data) {
        head->left = delete(data, head->left);
    }
    else if (data > head->data) {
        head->right = delete(data, head->right);
    }
    else {
        if (!head->left && !head->right) {
            free(head);
            return NULL;
        }
    }

    return head;
}

int count_nodes_at_level(Node* head, int target_level, int current_level) {
    if (!head) return 0;
    
    if (current_level == target_level) {
        return 1;
    }
    
    return count_nodes_at_level(head->left, target_level, current_level + 1) +
           count_nodes_at_level(head->right, target_level, current_level + 1);
} 

int count_width(Node* head) {
    if (!head) return 0;
    
    int max_depth = check_depth(head);
    int max_width = 0;
    
    for (int level = 0; level <= max_depth; level++) {
        int width = count_nodes_at_level(head, level, 0);
        if (width > max_width) {
            max_width = width;
        }
    }
    
    return max_width;
}


int main() {
    Node* head = initiate_tree(10);
    add(8, head);
    add(2, head);
    add(3, head);
    add(5, head);
    add(4, head);
    add(12, head);
    add(15, head);
    
    printf("Исходное дерево:\n");
    print_tree(head);
    printf("Глубина: %d\n", check_depth(head));
    printf("Ширина: %d\n", count_width(head));
    
    delete(4, head);
    
    printf("\nПосле удаления узла 4:\n");
    print_tree(head);
    printf("Глубина: %d\n", check_depth(head));
    printf("Ширина: %d\n", count_width(head));

    return 0;
}