extern "C" {
    #include "src/tree.h"
}
#include <gtest/gtest.h>
#include <cmath>

// Хелпер: передаём строковый литерал как char* (функции не изменяют строку)
static inline char* cs(const char* s) { return const_cast<char*>(s); }

// Вспомогательная функция: проверка AVL-свойства
int is_avl_valid(Node* node) {
    if (node == NULL) return 1;
    int balance = balance_factor(node);
    if (balance < -1 || balance > 1) return 0;
    return is_avl_valid(node->left) && is_avl_valid(node->right);
}

// Тесты avl_insert

TEST(AVLInsert, InsertSingleNode) {
    Node* root = avl_insert(cs("One"), 1.1, NULL);
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->key, "One");
    EXPECT_DOUBLE_EQ(root->data, 1.1);
}

TEST(AVLInsert, InsertMultipleNodes) {
    Node* root = NULL;
    root = avl_insert(cs("One"),   1.1, root);
    root = avl_insert(cs("Two"),   2.2, root);
    root = avl_insert(cs("Three"), 3.3, root);

    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(std::isnan(search(cs("One"),   root)));
    EXPECT_FALSE(std::isnan(search(cs("Two"),   root)));
    EXPECT_FALSE(std::isnan(search(cs("Three"), root)));
}

TEST(AVLInsert, InsertMaintainsAVLProperty) {
    Node* root = NULL;
    root = avl_insert(cs("A"), 1.0, root);
    root = avl_insert(cs("B"), 2.0, root);
    root = avl_insert(cs("C"), 3.0, root);  // вызывает ротацию
    root = avl_insert(cs("D"), 4.0, root);
    root = avl_insert(cs("E"), 5.0, root);  // вызывает ротацию

    EXPECT_TRUE(is_avl_valid(root));
}

TEST(AVLInsert, InsertDuplicateKeyIgnored) {
    Node* root = NULL;
    root = avl_insert(cs("One"), 1.1, root);
    root = avl_insert(cs("One"), 9.9, root);  // дубликат — должен быть проигнорирован

    EXPECT_DOUBLE_EQ(search(cs("One"), root), 1.1);  // значение не изменилось
}

// Тесты search

TEST(Search, FindExistingKey) {
    Node* root = NULL;
    root = avl_insert(cs("One"), 1.1, root);
    root = avl_insert(cs("Two"), 2.2, root);

    EXPECT_DOUBLE_EQ(search(cs("One"), root), 1.1);
    EXPECT_DOUBLE_EQ(search(cs("Two"), root), 2.2);
}

TEST(Search, FindNonExistingKey) {
    Node* root = NULL;
    root = avl_insert(cs("One"), 1.1, root);

    EXPECT_TRUE(std::isnan(search(cs("Two"), root)));
}

TEST(Search, SearchInEmptyTree) {
    EXPECT_TRUE(std::isnan(search(cs("One"), NULL)));
}

TEST(Search, SearchEmptyKey) {
    Node* root = avl_insert(cs("One"), 1.1, NULL);
    EXPECT_TRUE(std::isnan(search(cs(""), root)));
}

// Тесты avl_delete

TEST(AVLDelete, DeleteLeafNode) {
    Node* root = NULL;
    root = avl_insert(cs("One"), 1.1, root);
    root = avl_insert(cs("Two"), 2.2, root);

    root = avl_delete(root, cs("Two"));

    EXPECT_TRUE(std::isnan(search(cs("Two"), root)));
    EXPECT_FALSE(std::isnan(search(cs("One"), root)));
}

TEST(AVLDelete, DeleteNodeWithTwoChildren) {
    Node* root = NULL;
    root = avl_insert(cs("B"), 2.0, root);
    root = avl_insert(cs("A"), 1.0, root);
    root = avl_insert(cs("C"), 3.0, root);

    root = avl_delete(root, cs("B"));  // узел с двумя потомками

    EXPECT_TRUE(std::isnan(search(cs("B"), root)));
    EXPECT_FALSE(std::isnan(search(cs("A"), root)));
    EXPECT_FALSE(std::isnan(search(cs("C"), root)));
}

TEST(AVLDelete, DeleteMaintainsAVLProperty) {
    Node* root = NULL;
    root = avl_insert(cs("A"), 1.0, root);
    root = avl_insert(cs("B"), 2.0, root);
    root = avl_insert(cs("C"), 3.0, root);
    root = avl_insert(cs("D"), 4.0, root);
    root = avl_insert(cs("E"), 5.0, root);

    root = avl_delete(root, cs("C"));
    root = avl_delete(root, cs("A"));

    EXPECT_TRUE(is_avl_valid(root));
}

TEST(AVLDelete, DeleteNonExistingKey) {
    Node* root = avl_insert(cs("One"), 1.1, NULL);
    Node* root_before = root;

    root = avl_delete(root, cs("Two"));  // не существует — дерево не меняется

    EXPECT_EQ(root, root_before);
}

TEST(AVLDelete, DeleteFromEmptyTree) {
    Node* root = avl_delete(NULL, cs("One"));
    EXPECT_EQ(root, nullptr);
}

// Тесты height_count и balance_factor

TEST(Height, EmptyTree) {
    EXPECT_EQ(height_count(NULL), 0);
}

TEST(Height, SingleNode) {
    Node* root = avl_insert(cs("A"), 1.0, NULL);
    EXPECT_EQ(height_count(root), 1);
}

TEST(Height, BalancedTree) {
    Node* root = NULL;
    root = avl_insert(cs("B"), 2.0, root);
    root = avl_insert(cs("A"), 1.0, root);
    root = avl_insert(cs("C"), 3.0, root);

    EXPECT_EQ(height_count(root), 2);
}

TEST(Balance, RootBalanced) {
    Node* root = NULL;
    root = avl_insert(cs("B"), 2.0, root);
    root = avl_insert(cs("A"), 1.0, root);
    root = avl_insert(cs("C"), 3.0, root);

    EXPECT_EQ(balance_factor(root), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
