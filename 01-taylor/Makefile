## 
#  This file is part of 01-taylor task.
# 
#  Makefile
#  Stanisław Grams
##

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99
LDFLAGS=-lm

main:	main.o taylor.o
main.o:	main.c
taylor.o: taylor.c

clean: 
	rm -f main main.o taylor.o
run: main
	./main
rmobj:
	rm -f main.o taylor.o
