CC     = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -O0 -g3

.PHONY: all clean run re

TRGT = main
SRCS = main.c


all:
	$(CC) $(CFLAGS) main.c -o main

clean:
	@rm -f main
	@echo "clean"


run: all
	@./main 1000000

re: clean all

