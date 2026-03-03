CC = gcc
CFLAGS = -Wall -Wextra

all: main test

main: main.c funcs.h
	$(CC) $(CFLAGS) main.c -o main

test: test.c funcs.h
	$(CC) $(CFLAGS) test.c -o test

run_tests: test
	./test

run: run_tests main
	./main

clean:
	rm -f main test *.o

.PHONY: all clean run_tests run



