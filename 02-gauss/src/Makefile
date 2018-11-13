## 
#  This file is part of 02-gauss task.
# 
#  src/Makefile
#  Stanisław Grams
##
CC=g++
CFLAGS=-Wall -Werror -D_GNU_SOURCE -g -std=gnu99

# main targets
all: main.o gauss.o util.o

# *.c
main.o: main.cc
gauss.o: gauss.cc
util.o: util.cc

# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f main.o xor.o util.o