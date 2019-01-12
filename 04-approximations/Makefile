## 
#  This file is part of 04-approximations task.
# 
#  Makefile
#  Stanisław Grams
##
CC=g++
CXXFLAGS=-Wall -Werror -pedantic -std=c++0x $(pkg-config --cflags eigen3)
LDFLAGS=-pthread $(pkg-config --cflags eigen3)

SRCDIR=src
OUTNAME=approximations

# main targets
all:
	+$(MAKE) -C $(SRCDIR)
	+$(CC) -o $(OUTNAME) $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

build:
	+$(MAKE) all

run:
	+./approximations

# other procedures
.PHONY:
	clean
clean:
	+rm -f $(OUTNAME)
	+$(MAKE) -C $(SRCDIR) clean
rmobj:
	+$(MAKE) -C $(SRCDIR) rmobj
rmcsv:
	+rm csv/*.csv
super:
	+$(MAKE) clean && $(MAKE) -j8 && $(MAKE) run

rebuild:
	+$(MAKE) clean && $(MAKE) all
