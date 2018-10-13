/*
 *  This file is part of 01-taylor task.
 *
 *  taylor.h
 *  Stanisław Grams
 */
#ifndef TAYLOR_H_
#define TAYLOR_H_
#include <glib.h>
#include <quadmath.h>
// Defining macros
#define MAX_PREC 32
// Defining basic functions to operate on 128 bit
// floating-point precision numbers
char *      taylor_print (__float128 numb);
// Redefinition of math functions using basic
// mathematical operations.
gint64      taylor_factorial (gint64 n);
__float128  taylor_pow (__float128 x, gint64 y);

// Functions realising given task
__float128  taylor_func1 (__float128 x);
#endif // TAYLOR_H_
