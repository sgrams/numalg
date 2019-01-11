## 
#  This file is part of 04-approximations task.
# 
#  src/Makefile
#  Stanisław Grams <sgrams@fmdx.pl>
##
CC=g++
CXXFLAGS=-Wall -Werror -pedantic -std=c++0x -g
LDFLAGS=-pthread

# main targets
all: matrix.o generator.o protocol.o util.o main.o

# *.o: *.cc
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
