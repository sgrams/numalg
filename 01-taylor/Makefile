## 
#  This file is part of 01-taylor task.
# 
#  Makefile
#  Stanisław Grams
##

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 $(shell pkg-config --cflags glib-2.0) -pthread
LDFLAGS=-lm $(shell pkg-config --libs glib-2.0) -lquadmath -pthread

main:	main.o taylor.o util.o
main.o:	main.c
util.o: util.c
taylor.o: taylor.c

clean: 
	rm -f main main.o taylor.o
run: main
	./main
rmobj:
	rm -f main.o taylor.o
