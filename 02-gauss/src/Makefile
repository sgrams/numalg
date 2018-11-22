## 
#  This file is part of 02-gauss task.
# 
#  src/Makefile
#  Stanisław Grams
##
CC=g++
CFLAGS=-Wall -Werror -Wall -pedantic -std=c++0x
LDFLAGS=-lgmpxx -lgmp -pthread

# main targets
all: gauss.o util.o main.o

# *.c
gauss.o: gauss.cc
util.o: util.cc
main.o: main.cc
# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f gauss.o util.o main.o