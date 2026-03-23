CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

SRC_DIR = src
TESTS_DIR = tests

HEADERS = $(SRC_DIR)/calculate_tree.h $(SRC_DIR)/check_priority.h $(SRC_DIR)/rpn_to_tree.h \
          $(SRC_DIR)/rpn.h $(SRC_DIR)/stack.h $(SRC_DIR)/tree.h $(SRC_DIR)/validation.h

main: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(SRC_DIR)/main $(LDFLAGS)

tests: $(TESTS_DIR)/tests.c $(HEADERS)
	$(CC) $(CFLAGS) $(TESTS_DIR)/tests.c -o $(TESTS_DIR)/tests $(LDFLAGS)

run: main run_tests
	./$(SRC_DIR)/main

run_tests: tests
	./$(TESTS_DIR)/tests

clean:
	rm -f $(SRC_DIR)/main $(TESTS_DIR)/tests

all: main tests

.PHONY: run run_tests clean all
