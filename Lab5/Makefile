SRC_DIR = src
CC = gcc
CC+ = g++
CFLAGS = -Wall -Wextra

GTEST_INC = /opt/homebrew/include
GTEST_LIB = /opt/homebrew/lib


test: tests.cpp
	$(CC+) -std=c++17 tests.cpp -o tests -I$(GTEST_INC) -L$(GTEST_LIB) -lgtest -lgtest_main

benchmark: $(SRC_DIR)/benchmark.c
	$(CC) $(CFLAGS) $(SRC_DIR)/benchmark.c -o $(SRC_DIR)/benchmark

main: $(SRC_DIR)/main.c $(SRC_DIR)/matrix.h $(SRC_DIR)/dijkstra.h
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(SRC_DIR)/main

run: test benchmark main
	./tests && ./$(SRC_DIR)/benchmark && ./$(SRC_DIR)/main

run_tests: test
	./tests


