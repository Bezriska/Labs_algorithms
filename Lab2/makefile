CC = gcc
CFLAGS = -Wall -Wextra

all: main

main: main.c help.h read.h sort.h search.h
	$(CC) $(CFLAGS) main.c -o main

run: main run_tests
	./main

run_tests: test
	./test

test: test.c help.h read.h sort.h search.h
	$(CC) $(CFLAGS) test.c -o test