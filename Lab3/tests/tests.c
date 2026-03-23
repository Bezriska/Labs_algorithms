#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/validation.h"
#include "../src/rpn.h"
#include "../src/rpn_to_tree.h"
#include "../src/tree.h"
#include "../src/calculate_tree.h"

// ТЕСТЫ ВАЛИДАЦИИ

void test_validation() {
    printf("Testing validation...\n");
    
    // Валидные выражения
    assert(validation("2+3") == 1);
    assert(validation("(2+3)*4") == 1);
    assert(validation("123+456") == 1);
    assert(validation("a+b*c") == 1);
    assert(validation("x1+y2") == 1);
    assert(validation("2 + 3") == 1);
    
    // Невалидные выражения
    assert(validation("2++3") == 0);
    assert(validation("2+") == 0);
    assert(validation("+2") == 0);
    assert(validation("(2+3") == 0);
    assert(validation("2+3)") == 0);
    assert(validation("2 3") == 0);
    
    printf("All validation tests passed\n");
}

// ТЕСТЫ RPN

void test_rpn_conversion() {
    printf("Testing RPN conversion...\n");
    
    char* result;
    
    result = rpn("2+3");
    assert(strcmp(result, "2 3 +") == 0);
    free(result);
    
    result = rpn("2+3*4");
    assert(strcmp(result, "2 3 4 * +") == 0);
    free(result);
    
    result = rpn("(2+3)*4");
    assert(strcmp(result, "2 3 + 4 *") == 0);
    free(result);
    
    result = rpn("123+456");
    assert(strcmp(result, "123 456 +") == 0);
    free(result);
    
    result = rpn("2-3-4");
    assert(strcmp(result, "2 3 - 4 -") == 0);
    free(result);
    
    result = rpn("2^3^4");
    assert(strcmp(result, "2 3 4 ^ ^") == 0);
    free(result);
    
    result = rpn("a+b*c");
    assert(strcmp(result, "a b c * +") == 0);
    free(result);
    
    printf("All RPN tests passed\n");
}

// ТЕСТЫ ПОСТРОЕНИЯ ДЕРЕВА

void test_tree_building() {
    printf("Testing tree building...\n");
    
    char* rpn_str = rpn("2+3");
    Node* tree = rpn_to_tree(rpn_str);
    assert(tree != NULL);
    assert(tree->type == NODE_OPERATOR);
    assert(tree->value.op == '+');
    assert(tree->left->type == NODE_NUMBER);
    assert(tree->left->value.number == 2);
    assert(tree->right->type == NODE_NUMBER);
    assert(tree->right->value.number == 3);
    free(rpn_str);
    
    rpn_str = rpn("123+456");
    tree = rpn_to_tree(rpn_str);
    assert(tree->left->value.number == 123);
    assert(tree->right->value.number == 456);
    free(rpn_str);
    
    rpn_str = rpn("a+b");
    tree = rpn_to_tree(rpn_str);
    assert(tree->left->type == NODE_VARIABLE);
    assert(tree->left->value.variable == 'a');
    assert(tree->right->type == NODE_VARIABLE);
    assert(tree->right->value.variable == 'b');
    free(rpn_str);
    
    printf("All tree building tests passed\n");
}

// ТЕСТЫ УПРОЩЕНИЯ

void test_simplification() {
    printf("Testing simplification (removing unit factors)...\n");
    
    char* rpn_str;
    Node* tree;
    
    rpn_str = rpn("5*1");
    tree = rpn_to_tree(rpn_str);
    tree = remove_unit_factors_tree(tree);
    assert(tree->type == NODE_NUMBER);
    assert(tree->value.number == 5);
    free(rpn_str);
    
    rpn_str = rpn("1*5");
    tree = rpn_to_tree(rpn_str);
    tree = remove_unit_factors_tree(tree);
    assert(tree->type == NODE_NUMBER);
    assert(tree->value.number == 5);
    free(rpn_str);
    
    rpn_str = rpn("(2+3)*1");
    tree = rpn_to_tree(rpn_str);
    tree = remove_unit_factors_tree(tree);
    assert(tree->type == NODE_OPERATOR);
    assert(tree->value.op == '+');
    free(rpn_str);
    
    rpn_str = rpn("5*1*1");
    tree = rpn_to_tree(rpn_str);
    tree = remove_unit_factors_tree(tree);
    assert(tree->type == NODE_NUMBER);
    assert(tree->value.number == 5);
    free(rpn_str);
    
    rpn_str = rpn("5+1");
    tree = rpn_to_tree(rpn_str);
    Node* original = tree;
    tree = remove_unit_factors_tree(tree);
    assert(tree == original);
    assert(tree->type == NODE_OPERATOR);
    free(rpn_str);
    
    printf("All simplification tests passed\n");
}

// ТЕСТЫ ВЫЧИСЛЕНИЯ

void test_calculation() {
    printf("Testing calculation...\n");
    
    char* rpn_str;
    Node* tree;
    
    rpn_str = rpn("2+3");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->type == NODE_NUMBER);
    assert(tree->value.number == 5);
    free(rpn_str);
    
    rpn_str = rpn("10-3");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->value.number == 7);
    free(rpn_str);
    
    rpn_str = rpn("4*5");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->value.number == 20);
    free(rpn_str);
    
    rpn_str = rpn("15/3");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->value.number == 5);
    free(rpn_str);
    
    rpn_str = rpn("2^3");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->value.number == 8);
    free(rpn_str);
    
    rpn_str = rpn("(2+3)*4");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->value.number == 20);
    free(rpn_str);
    
    rpn_str = rpn("2+a");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->type == NODE_OPERATOR);
    assert(tree->value.op == '+');
    free(rpn_str);
    
    rpn_str = rpn("(2+3)*a");
    tree = rpn_to_tree(rpn_str);
    tree = simplify(tree);
    assert(tree->type == NODE_OPERATOR);
    assert(tree->value.op == '*');
    assert(tree->left->type == NODE_NUMBER);
    assert(tree->left->value.number == 5);
    assert(tree->right->type == NODE_VARIABLE);
    free(rpn_str);
    
    printf("All calculation tests passed\n");
}

// КОМПЛЕКСНЫЕ ТЕСТЫ

void test_complex() {
    printf("Testing complex pipeline...\n");
    
    char* expr = "(123+456-1)*20*1";
    assert(validation(expr) == 1);
    
    char* rpn_str = rpn(expr);
    assert(strcmp(rpn_str, "123 456 + 1 - 20 * 1 *") == 0);
    
    Node* tree = rpn_to_tree(rpn_str);
    assert(tree != NULL);
    
    tree = remove_unit_factors_tree(tree);
    tree = simplify(tree);
    
    assert(tree->type == NODE_NUMBER);
    assert(tree->value.number == 11560);
    
    free(rpn_str);
    
    expr = "(10+5)*b*1";
    assert(validation(expr) == 1);
    
    rpn_str = rpn(expr);
    tree = rpn_to_tree(rpn_str);
    tree = remove_unit_factors_tree(tree);
    tree = simplify(tree);
    
    assert(tree->type == NODE_OPERATOR);
    assert(tree->left->type == NODE_NUMBER);
    assert(tree->left->value.number == 15);
    assert(tree->right->type == NODE_VARIABLE);
    
    free(rpn_str);
    
    printf("All complex tests passed\n");
}

// ГЛАВНАЯ ФУНКЦИЯ

int main() {
    printf("=================================================\n");
    printf("ТЕСТЫ LAB3: RPN И ДЕРЕВО ВЫРАЖЕНИЙ\n");
    printf("=================================================\n\n");

    test_validation();
    test_rpn_conversion();
    test_tree_building();
    test_simplification();
    test_calculation();
    test_complex();

    printf("\n=================================================\n");
    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
    printf("=================================================\n");

    return 0;
}
