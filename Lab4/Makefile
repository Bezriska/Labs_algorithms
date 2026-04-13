CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
GTEST_INC = /tmp/gtest/googletest/include
GTEST_LIB = /tmp/libgtest.a

run: main run_tests
	./$(SRC_DIR)/main

main: $(SRC_DIR)/tree.h $(SRC_DIR)/read.h
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(SRC_DIR)/main

tests: $(SRC_DIR)/tests.cpp
	g++ -std=c++17 -isystem $(GTEST_INC) -pthread $(SRC_DIR)/tests.cpp $(GTEST_LIB) -o $(SRC_DIR)/tests
# -std=c++17	стандарт С++
# -isystem	подключает папку с заголовками и помечает директорию как систменую
# -pthread	включает поддержку многопоточности, без него линковщик не найдет символы из pthread

run_tests: tests
	./$(SRC_DIR)/tests