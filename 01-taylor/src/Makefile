## 
#  This file is part of 01-taylor task.
# 
#  src/Makefile
#  Stanisław Grams <sgrams@fmdx.pl>
##
CC=gcc
CFLAGS=$(shell pkg-config --cflags glib-2.0) -Wall -Werror -std=gnu11 -g
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lquadmath -pthread

# main targets
all: util.o taylor.o main.o

# *.o: *.cc
util.o: util.c
taylor.o: taylor.c
main.o: main.c

# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f util.o taylor.o main.o
