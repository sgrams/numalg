/*
 * This file is part of 01-taylor task.
 *
 * taylor.c
 * Stanisław Grams
 */
#include "taylor.h"

/*
 * Returns 128 bit floating-point number
 * into a 32 byte long string of pointers.
 * Ended with '\0'.
 *
 * @arg    __float128  numb
 * @retval   char     *out
 *
 */
char *
taylor_print (__float128 numb) {
  char buf[MAX_PREC];
  quadmath_snprintf (buf, MAX_PREC * sizeof (char), "%.32Qf", numb);
  return g_strdup_printf ("%s", buf);
}

/*
 * Computes e ^ sin x with
 * built-in C functions.
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_func1 (__float128 x) {
  return (__float128)expq ((__float128)sinq (x));
}

/*
 * Computes factorial
 *
 * @arg    gint64 n
 * @retval gint64 result
 *
 */
gint64
taylor_factorial (gint64 n) {
  gint64 i;
  gint64 result = 1;

  if (n <= 1) {
    return 1;
  }
  for (i = 1; i <= n; i++)
  {
    result *= i;
  }
  return result;
}

/*
 * Result of calculating e ^ (sin x)
 * with Taylor formula extended at 0.
 *
 * @arg    __float128 x
 * @arg    __float128 precision
 * @retval __float128 result
 *
 */
__float128 maclaurin_func (__float128 x, __float128 precision) {
  int i;
  __float128 result = 0;

  for (i = 0; i < 19; i++)
  {
  }
  return result;
}

/*
 * Result of calculating x ^ y
 * with basic multiplication.
 *
 * @arg    __float128 x
 * @arg    gint64      y
 * @retval __float128 result
 *
 */
__float128
taylor_pow (__float128 x, gint64 y) {
  gsize i;
  __float128 result = 1.0;

  for (i = 0; i < y; ++i)
  {
    result *= x;
  }
  return result;
}
