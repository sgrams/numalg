## 
#  This file is part of 03-population_protocol task.
# 
#  src/Makefile
#  Stanisław Grams <sgrams@fmdx.pl>
##
CC=g++
CFLAGS=-Wall -Werror -Wall -pedantic -std=c++0x
LDFLAGS=-lgmpxx -lgmp -pthread

# main targets
all: protocols.o util.o main.o

# *.c
protocols.o: protocols.cc
util.o: util.cc
main.o: main.cc
# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f protocols.o util.o main.o
