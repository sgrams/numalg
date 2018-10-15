## 
#  This file is part of 01-taylor task.
# 
#  Makefile
#  Stanisław Grams
##

CC=gcc
CFLAGS=$(shell pkg-config --cflags glib-2.0) -pthread -Wall -Werror -std=gnu99
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lquadmath -pthread

taylor:	main.o taylor.o util.o
main.o:	main.c
util.o: util.c
taylor.o: taylor.c

clean: 
	rm -f taylor main.o taylor.o util.o
run: taylor
	./taylor
rmobj:
	rm -f main.o taylor.o util.o
