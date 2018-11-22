## 
#  This file is part of 02-gauss task.
# 
#  Makefile
#  Stanisław Grams
##
CC=g++
CFLAGS=-Wall -Werror -Wall -pedantic -std=c++0x
LDFLAGS=-lgmpxx -lgmp -pthread

SRCDIR=src
OUTNAME=gauss

# main targets
all:
	+$(MAKE) -C $(SRCDIR)
	+$(CC) -o $(OUTNAME) $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

# other procedures
.PHONY:
	clean
clean:
	+rm -f $(OUTNAME)
	+$(MAKE) -C $(SRCDIR) clean
rmobj:
	+$(MAKE) -C $(SRCDIR) rmobj
rmcsv:
	+rm -f double_tests.csv float_tests.csv mytype_tests.csv
