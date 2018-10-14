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
#define      MAX_BUF 1024

#define STR_MAX_PREC "64"

#define   Q_EXP_STEP 16
#define   Q_SIN_STEP 16
#define   Q_SUM_STEP 0.000001Q

#define INTERVAL_MIN -1.2Q
#define INTERVAL_MAX 1.2Q
#define MAX_ELEMENTS 2400000

// Defining basic functions to operate on 128 bit
// floating-point precision numbers
char       *taylor_print (__float128 numb);

// Redefinition of math functions using basic
// mathematical operations.
__float128  taylor_fac     (__float128 n);
__float128  taylor_pow     (__float128 x, gint64 y);
__float128  taylor_sin     (__float128 x);
__float128  taylor_sin_rev (__float128 x);
__float128  taylor_exp     (__float128 x);
__float128  taylor_exp_rev (__float128 x);

// Functions realising given task
__float128  taylor_func0 (__float128 x);
__float128  taylor_func1 (__float128 x);
__float128  taylor_func2 (__float128 x);
#endif // TAYLOR_H_
