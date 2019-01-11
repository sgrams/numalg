## 
#  This file is part of 04-approximations task.
# 
#  Makefile
#  Stanisław Grams
##
CC=g++
CFLAGS=-Wall -Werror -pedantic -std=c++0x
LDFLAGS=-pthread

SRCDIR=src
OUTNAME=approximations

# main targets
all:
	+$(MAKE) -C $(SRCDIR)
	+$(CC) -o $(OUTNAME) $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

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
