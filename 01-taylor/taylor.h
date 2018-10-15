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

#define   Q_MAX_STEP 4
#define   Q_EXP_STEP Q_MAX_STEP
#define   Q_SIN_STEP Q_EXP_STEP

// Defining basic functions to operate on 128 bit
// floating-point precision numbers
char       *taylor_print (__float128 numb);

// Redefinition of math functions using basic
// mathematical operations.
__float128  taylor_fac          (__float128 n);
__float128  taylor_pow          (__float128 x, gint64 y);

__float128  taylor_sin          (__float128 x, gint32 max_steps);
__float128  taylor_sin_rev      (__float128 x, gint32 max_steps);
__float128  taylor_sin_prev     (__float128 x, gint32 max_steps);
__float128  taylor_sin_prev_rev (__float128 x, gint32 max_steps);

__float128  taylor_exp          (__float128 x, gint32 max_steps);
__float128  taylor_exp_rev      (__float128 x, gint32 max_steps);
__float128  taylor_exp_prev     (__float128 x, gint32 max_steps);
__float128  taylor_exp_prev_rev (__float128 x, gint32 max_steps);

// Functions realising given task
__float128  taylor_func0 (__float128 x);
__float128  taylor_func1 (__float128 x, gint32 max_steps);
__float128  taylor_func2 (__float128 x, gint32 max_steps);
__float128  taylor_func3 (__float128 x, gint32 max_steps);
__float128  taylor_func4 (__float128 x, gint32 max_steps);
#endif // TAYLOR_H_
