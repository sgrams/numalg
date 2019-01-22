## 
#  This file is part of 01-taylor task.
# 
#  Makefile
#  Stanisław Grams
##
CC=gcc
CFLAGS=$(shell pkg-config --cflags glib-2.0) -Wall -Werror -pedantic -std=gnu11
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lquadmath -pthread

SRCDIR=src
OUTNAME=taylor

# main targets
all:
	+$(MAKE) -C $(SRCDIR)
	+$(CC) -o $(OUTNAME) $(SRCDIR)/*.o $(CFLAGS) $(LDFLAGS)

run:
	+./$(OUTNAME)

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
