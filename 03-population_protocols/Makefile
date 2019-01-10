## 
#  This file is part of 03-population_protocol task.
# 
#  Makefile
#  Stanisław Grams
##
CC=g++
CFLAGS=-Wall -Werror -pedantic -std=c++0x
LDFLAGS=-pthread

SRCDIR=src
OUTNAME=protocols

# main targets
all:
	+$(MAKE) -C $(SRCDIR)
	+$(CC) -o $(OUTNAME) $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

run:
	+./protocols

# other procedures
.PHONY:
	clean
clean:
	+rm -f $(OUTNAME)
	+$(MAKE) -C $(SRCDIR) clean
rmobj:
	+$(MAKE) -C $(SRCDIR) rmobj
rmcsv:
	+rm *.csv
