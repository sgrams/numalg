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
  char buf[MAX_BUF];
  quadmath_snprintf (buf, MAX_BUF * sizeof (char), "%."STR_MAX_PREC"Qf", numb);
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
taylor_func0 (__float128 x) {
  return (__float128)expq ((__float128)sinq (x));
}

/*
 * Computes e ^ sin x by
 * calculating Taylor series formula:
 * ((-1)^n / (2n+1)! * x ^(2n+1))^n / (2n+1)!
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_func1 (__float128 x) {
  return taylor_exp (taylor_sin (x)); 
}

/*
 * Computes e ^ sin x by
 * calculating Taylor series formula:
 * ((-1)^n / (2n+1)! * x ^(2n+1))^n / (2n+1)!
 * 
 * but in a reversed way
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_func2 (__float128 x) {
  return taylor_exp_rev (taylor_sin_rev (x)); 
}

/*
 * Computes factorial
 *
 * @arg    __float128 n
 * @retval __float128 result
 *
 */
__float128
taylor_fac (__float128 n) {
  __float128 result = 1.0Q;
  __float128 i;

  if (n <= 1.0Q) {
    return 1.0Q;
  }
  for (i = 1.0Q; i <= n; i++)
  {
    result *= i;
  }
  return (__float128) result;
}

/*
 * Result of calculating x ^ y
 * with basic multiplication.
 *
 * @arg    __float128 x
 * @arg    gint64     y
 * @retval __float128 result
 *
 */
__float128
taylor_pow (__float128 x, gint64 y) {
  __float128 result = 1.0Q;
       gsize i;

  for (i = 0; i < y; ++i)
  {
    result *= x;
  }
  return result;
}

/*
 * Computes sin x
 * by calculating Taylor series formula:
 * (-1)^n / (2n+1)! * x ^(2n+1)
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_sin (__float128 x) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = 0; i < Q_SIN_STEP; ++i)
  {
    result += taylor_pow (-1.0Q, i) / taylor_fac (2.0Q * (__float128)i + 1.0Q)
      * taylor_pow (x, 2.0Q * (__float128)i + 1.0Q);
  }
  return result;
}

/*
 * Computes sin x
 * by calculating Taylor series formula:
 * (-1)^n / (2n+1)! * x ^(2n+1)
 * in a reversed way
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_sin_rev (__float128 x) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = Q_SIN_STEP - 1; i+1 > 0; --i)
  {
    result += taylor_pow (-1.0Q, i) / taylor_fac (2.0Q * (__float128)i + 1.0Q)
      * taylor_pow (x, 2.0Q * (__float128)i + 1.0Q);
  }
  return result;
}

/*
 * Computes e^x
 * by calculating Taylor series formula:
 * x^k / k!
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_exp (__float128 x) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = 0; i < Q_EXP_STEP; ++i)
  {
    result += taylor_pow (x, i) / taylor_fac (i);
  }

  return result;
}

/*
 * Computes e^x
 * by calculating Taylor series formula:
 * x^k / k!
 * in a reversed way
 *
 * @arg    __float128 x
 * @retval __float128 result
 *
 */
__float128
taylor_exp_rev (__float128 x) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = Q_EXP_STEP - 1; i+1 > 0; --i)
  {
    result += taylor_pow (x, i) / taylor_fac (i);
  }

  return result;
}