CC = gcc
CFLAGS = -Wall -Werror

main: main.o
	$(CC) $(CFLAGS) main.c -o main

test:
	./main test.txt

.PHONY: test