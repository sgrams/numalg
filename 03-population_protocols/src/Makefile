## 
#  This file is part of 03-population_protocol task.
# 
#  src/Makefile
#  Stanisław Grams <sgrams@fmdx.pl>
##
CC=g++
CFLAGS=-Wall -Werror -Wall -pedantic -std=c++0x
LDFLAGS=-pthread

# main targets
all: probability.o matrix.o generator.o protocol.o util.o main.o

# *.o: *.cc
probability.o: probability.cc
matrix.o: matrix.cc
generator.o: generator.cc
protocol.o: protocol.cc
util.o: util.cc
main.o: main.cc

# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f probability.o matrix.o generator.o protocol.o util.o main.o
