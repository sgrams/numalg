## 
#  This file is part of 04-approximations task.
# 
#  src/Makefile
#  Stanisław Grams <sgrams@fmdx.pl>
##
CC=g++
CXXFLAGS=-Wall -Werror -pedantic -std=c++0x -g $(pkg-config --cflags eigen3)
LDFLAGS=-pthread $(pkg-config --cflags eigen3)

# main targets
all: main.o matrix.o util.o protocol.o generator.o probability.o

# *.o: *.cc
sparsematrix.o: sparsematrix.cc
sparsegenerator.o: sparsegenerator.cc
approximation.o: approximation.cc
probability.o: probability.cc
generator.o: generator.cc
protocol.o: protocol.cc
util.o: util.cc
matrix.o: matrix.cc
main.o: main.cc

# other procedures
.PHONY: clean
clean:  rmobj
rmobj:
	rm -f matrix.o generator.o protocol.o util.o main.o
