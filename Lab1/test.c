#include "funcs.h"
#include <assert.h>

void test_initiate() {
    Node* head = initiate_tree(2);

    assert(search_data(2, head));
    printf("test_initiate: OK\n");
}


void test_add() {
    Node* head = initiate_tree(2);

    add(5, head);

    assert(search_data(5, head));
    printf("test_add: OK\n");
}


void test_check_depth() {
    Node* head = initiate_tree(3);

    add(2, head);
    add(1, head);

    assert(check_depth(head) == 2);
    printf("test_check_depth: OK\n");
}


void test_child_exist() {
    Node* head = initiate_tree(5);

    assert(child_exist(head) == 0);

    add(3, head);
    add(7, head);

    assert(child_exist(head) == 1);
    printf("test_child_exist: OK\n");
}


void test_delete_node() {
    Node* head = initiate_tree(5);

    add(3, head);

    head = delete_node(3, head);

    assert(search_data(3, head) == 0);
    printf("test_delete_node: OK\n");
}


void test_count_nodes_at_level() {
    Node* head = initiate_tree(5);

    add(2, head);
    add(6, head);

    assert(count_nodes_at_level(head, 0, 0) == 1);
    assert(count_nodes_at_level(head, 1, 0) == 2);
    printf("test_count_nodes_at_level: OK\n");
}


void test_count_width() {
    Node* head = initiate_tree(5);

    add(2, head);
    add(1, head);
    add(6, head);

    assert(count_width(head) == 2);
    printf("test_count_width: OK\n");
}


int main(void) {
    printf("Запуск тестов...\n\n");
    
    test_initiate();
    test_add();
    test_check_depth();
    test_child_exist();
    test_delete_node();
    test_count_nodes_at_level();
    test_count_width();

    printf("\nВсе тесты пройдены успешно!\n");
    return 0;
}