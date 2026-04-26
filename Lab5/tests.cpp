extern "C" {
    #include "src/dijkstra.h"
    #include "src/matrix.h"
}
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// Записывает строку во временный файл и перенаправляет stdin на него.
// Возвращает путь к файлу — нужно удалить после теста.
void mock_stdin(const char* input) {
    FILE* tmp = fopen("/tmp/test_stdin.txt", "w");
    fputs(input, tmp);
    fclose(tmp);
    freopen("/tmp/test_stdin.txt", "r", stdin);
}

// Матрица 2x2: все значения корректные (0 и положительные)
TEST(Matrix, AllValidValues) {
    mock_stdin("0 5\n3 0\n");
    int** m = write_matrix_from_terminal(2);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 5);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 0);
    free_matrix(m, 2);
}

// Валидация: сначала вводится отрицательное значение, затем корректное
TEST(Matrix, NegativeValue) {
    // -1 - невалидно, затем 7 - валидно; остальные сразу корректны
    mock_stdin("-1\n7\n0\n0\n0\n");
    int** m = write_matrix_from_terminal(2);
    EXPECT_EQ(m[0][0], 7); // после повтора должно быть 7
    EXPECT_EQ(m[0][1], 0);
    free_matrix(m, 2);
}

// Тест функции take_elememt
TEST(Matrix, TakeElement) {
    mock_stdin("0\n1\n5\n1\n");
    int** m = write_matrix_from_terminal(2);
    int one_one = take_element(1, 1, m);
    int one_two = take_element(1, 2, m);
    EXPECT_EQ(one_one, 0);
    EXPECT_EQ(one_two, 1);
    free_matrix(m, 2);
}

// Граф из одной вершины - расстояние до себя = 0
TEST(Dijkstra, SingleVertex) {
    mock_stdin("0\n");
    int** m = write_matrix_from_terminal(1);
    int* res = dijkstra_algorithm(m, 1);
    EXPECT_EQ(res[0], 0);
    free(res);
    free_matrix(m, 1);
}

// Два узла, прямое ребро 0->1 с весом 5
TEST(Dijkstra, TwoVertices) {
    mock_stdin("0\n5\n0\n0\n");
    int** m = write_matrix_from_terminal(2);
    int* res = dijkstra_algorithm(m, 2);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 5);
    free(res);
    free_matrix(m, 2);
}

// Недостижимая вершина - расстояние должно остаться INT_MAX
TEST(Dijkstra, UnreachableVertex) {
    mock_stdin("0\n3\n0\n0\n0\n0\n0\n0\n0\n");
    int** m = write_matrix_from_terminal(3);
    int* res = dijkstra_algorithm(m, 3);
    EXPECT_EQ(res[2], INT_MAX);
    free(res);
    free_matrix(m, 3);
}

// Кратчайший путь через промежуточную вершину
// 0->1 (10), 0->2 (3), 2->1 (2) -> до 1 должно быть 5, а не 10
TEST(Dijkstra, ShortestPathThroughIntermediate) {
    mock_stdin("0\n10\n3\n0\n0\n0\n0\n0\n0\n2\n0\n0\n0\n0\n0\n0\n");
    int** m = write_matrix_from_terminal(4);
    int* res = dijkstra_algorithm(m, 4);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 5); // 0->2->1: 3+2=5, короче чем 0->1: 10
    EXPECT_EQ(res[2], 3);
    EXPECT_EQ(res[3], INT_MAX);
    free(res);
    free_matrix(m, 4);
}

// Линейная цепочка: 0->1->2->3
TEST(Dijkstra, LinearChain) {
    mock_stdin("0\n1\n0\n0\n0\n0\n2\n0\n0\n0\n0\n4\n0\n0\n0\n0\n");
    int** m = write_matrix_from_terminal(4);
    int* res = dijkstra_algorithm(m, 4);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 1);
    EXPECT_EQ(res[2], 3);
    EXPECT_EQ(res[3], 7);
    free(res);
    free_matrix(m, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}