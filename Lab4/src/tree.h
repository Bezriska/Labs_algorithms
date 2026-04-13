# ifndef TREE_H
# define TREE_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    char key[7];
    double data;

    struct Node* left;
    struct Node* right;
    
    int height;
} Node;

int height_count(Node* head) {
    if (head == NULL) return 0;

    int left_h = height_count(head->left);
    int right_h = height_count(head->right);

    return (left_h > right_h ? left_h : right_h) + 1;
}



Node* right_rotate(Node* n) {
    Node* new_root = n->left;
    Node* right_root = new_root->right;

    new_root->right = n;
    n->left = right_root;

    n->height = 1 + MAX(height_count(n->left), height_count(n->right));
    new_root->height = 1 + MAX(height_count(new_root->left), height_count(new_root->right));

    return new_root;
}


Node* left_rotate(Node* n) {
    Node* new_root = n->right;
    Node* left_root = new_root->left;

    new_root->left = n;
    n->right = left_root;

    n->height = 1 + MAX(height_count(n->left), height_count(n->right));
    new_root->height = 1 + MAX(height_count(new_root->left), height_count(new_root->right));

    return new_root;
}


int balance_factor(Node* n) {
    if (n == NULL) return 0;
    return height_count(n->left) - height_count(n->right);
}


Node* avl_insert(char* key, double data, Node* head) {
    if (head == NULL) {
        Node* n = (Node*)malloc(sizeof(Node));
        n->data = data;
        strcpy(n->key, key);
        n->height = 1;
        n->left = NULL;
        n->right = NULL;
        return n;
    }

    int cmp = strcmp(key, head->key);

    if (cmp == 0) {
        printf("Ошибка: ключи должны быть уникальны\n");
        return head;
    }

    if (cmp > 0)
        head->right = avl_insert(key, data, head->right);
    else
        head->left = avl_insert(key, data, head->left);

    head->height = 1 + MAX(height_count(head->left), height_count(head->right));

    int balance = balance_factor(head);

    if (balance > 1 && strcmp(key, head->left->key) < 0)
        return right_rotate(head);

    if (balance < -1 && strcmp(key, head->right->key) > 0)
        return left_rotate(head);

    if (balance > 1 && strcmp(key, head->left->key) > 0) {
        head->left = left_rotate(head->left);
        return right_rotate(head);
    }

    if (balance < -1 && strcmp(key, head->right->key) < 0) {
        head->right = right_rotate(head->right);
        return left_rotate(head);
    }

    return head;
}


Node* search_min_right(Node* head) {
    if (head == NULL) return NULL;
    if (!head->left) return head;
    return search_min_right(head->left);
}


Node* del_min_right(Node* head) {
    if (head == NULL) return NULL;
    
    if (!head->left) {
        Node* temp = head->right;
        free(head);
        return temp;
    }

    head->left = del_min_right(head->left);
    
    return head;
}


Node* avl_delete(Node* head, char* key) {
    if (head == NULL) return NULL;

    int cmp = strcmp(key, head->key);

    if (cmp > 0)  {
        head->right = avl_delete(head->right, key);
    }

    if (cmp < 0) {
        head->left = avl_delete(head->left, key);
    }

    if (cmp == 0) {
        if (!head->left && !head->right) {
            free(head);
            return NULL;
        }

        if (head->left && !head->right) {
            Node* child = head->left;
            free(head);
            return child;
        }
        
        if (head->right && !head->left) {
            Node* child = head->right;
            free(head);
            return child;
        }

        if (head->right && head->left) {
            Node* min = search_min_right(head->right);
            strcpy(head->key, min->key);
            head->data = min->data;
            head->right = del_min_right(head->right);
        }
    }

    head->height = 1 + MAX(height_count(head->left), height_count(head->right));

    int balance = balance_factor(head);

    if (balance > 1 && balance_factor(head->left) >= 0)
        return right_rotate(head);

    if (balance > 1 && balance_factor(head->left) < 0) {
        head->left = left_rotate(head->left);
        return right_rotate(head);
    }

    if (balance < -1 && balance_factor(head->right) <= 0)
        return left_rotate(head);

    if (balance < -1 && balance_factor(head->right) > 0) {
        head->right = right_rotate(head->right);
        return left_rotate(head);
    }

    return head;
}


void print_tree_recursive(Node* node, int space, FILE* fp) {
    if (node == NULL) return;

    space += 6;

    print_tree_recursive(node->right, space, fp);

    printf("\n");
    for (int i = 6; i < space; i++) printf(" ");
    printf("%s:%.2lf\n", node->key, node->data);

    if (fp) {
        fprintf(fp, "\n");
        for (int i = 6; i < space; i++) fprintf(fp, " ");
        fprintf(fp, "%s:%.2lf\n", node->key, node->data);
    }

    print_tree_recursive(node->left, space, fp);
}

void print_tree(Node* head, FILE* fp) {
    printf("\n=== Дерево ===\n");
    if (fp) fprintf(fp, "\n=== Дерево ===\n");

    print_tree_recursive(head, 0, fp);

    printf("==============\n\n");
    if (fp) fprintf(fp, "==============\n\n");
}


double search(char* key, Node* head) {
    if (head == NULL) return NAN;
    if (strlen(key) == 0) return NAN;

    int cmp = strcmp(key, head->key);

    if (cmp > 0) {
        return search(key, head->right);
    }

    if (cmp < 0) {
        return search(key, head->left);
    }

    if (cmp == 0) {
        return head->data;
    }

    return NAN;
}





#endif