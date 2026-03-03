#include "funcs.h"

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
    
    if (search_data(4, head) == 1) {
        printf("Элемент %d найден\n", 4);
    } else {
        printf("Элемент %d не найден\n", 4);
    }

    delete_node(4, head);
    printf("Удален элемент %d\n", 4);
    
    if (search_data(4, head) == 1) {
        printf("Элемент %d найден\n", 4);
    } else {
        printf("Элемент %d не найден\n", 4);
    }

    return 0;
}