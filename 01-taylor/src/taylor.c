/*
 *  This file is part of 01-taylor task.
 *
 *  taylor.c
 *  Stanisław Grams
 */
#include "taylor.h"

/*
 * Converts 128 bit floating-point number
 * into a maximally MAX_BUF long char *.
 * Ends with '\0'.
 *
 * @arg    __float128  numb
 * @retval char       *out
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
taylor_func1 (__float128 x, gint32 max_steps) {
  return taylor_exp (taylor_sin (x, max_steps), max_steps); 
}

/*
 * Computes e ^ sin x by
 * calculating Taylor series formula:
 * ((-1)^n / (2n+1)! * x ^(2n+1))^n / (2n+1)!
 * with reversed summing
 *
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_func2 (__float128 x, gint32 max_steps) {
  return taylor_exp_rev (taylor_sin_rev (x, max_steps), max_steps); 
}

/*
 * Computes e ^ sin x by
 * calculating Taylor series formula:
 * ((-1)^n / (2n+1)! * x ^(2n+1))^n / (2n+1)!
 * 
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_func3 (__float128 x, gint32 max_steps) {
  return taylor_exp_prev (taylor_sin_prev (x, max_steps), max_steps); 
}

/*
 * Computes e ^ sin x by
 * calculating Taylor series formula:
 * ((-1)^n / (2n+1)! * x ^(2n+1))^n / (2n+1)!
 * with reversed summing
 * 
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_func4 (__float128 x, gint32 max_steps) {
  return taylor_exp_prev_rev (taylor_sin_prev_rev (x, max_steps), max_steps); 
}

/*
 * Optimizes argument for sin(x) function
 * basing on it's periodicity
 * 
 * @arg    __float128 x
 * @retval __float128 x
 * 
 */
__float128 taylor_optimize_arg (__float128 x) {
  while (x > (2.0Q * MY_PIq))
  {
    x -= (2.0Q * MY_PIq);
  }
  while (x < (-2.0Q * MY_PIq))
  {  
    x += (2.0Q * MY_PIq);
  }
  return x;
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
  if (y == 0) {
    return 1.0Q;
  }

  if (y % 2) {
    return x * taylor_pow (x, (y - 1.0Q) / 2.0Q) * taylor_pow (x, (y - 1.0Q) / 2.0Q);
  }

  return taylor_pow (x, y / 2.0Q) * taylor_pow (x, y / 2.0Q);
}

/*
 * Computes sin x
 * by calculating Taylor series formula:
 * (-1)^n / (2n+1)! * x ^(2n+1)
 *
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_sin (__float128 x, gint32 max_steps) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = 0; i < max_steps; ++i)
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
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_sin_rev (__float128 x, gint32 max_steps) {
  __float128 *array = g_malloc0 (max_steps * sizeof (__float128));
  __float128  result = 0.0Q;
        gsize i;
  
  for (i = 0; i < max_steps; ++i)
  {
    array[i] = (__float128)(taylor_pow (-1.0Q, i) / taylor_fac (2.0Q * (__float128)i + 1.0Q)
      * taylor_pow (x, 2.0Q * (__float128)i + 1.0Q));
  }

  for (i = max_steps - 1; i+1 > 0; --i)
  {
    result += array[i];
  }

  g_free (array);

  return result;
}

/*
 * Computes sin x
 * by calculating Taylor series formula:
 * (-1)^n / (2n+1)! * x ^(2n+1)
 * based on previous result
 * 
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_sin_prev (__float128 x, gint32 max_steps) {
  __float128 result = x;
       gsize i;

  for (i = 0; i < max_steps; ++i)
  {
    result *= taylor_pow (-1.0Q, i) * x * x / (2.0Q * i - 1.0Q);
  }
  return result;
}

/*
 * Computes sin x
 * by calculating Taylor series formula:
 * (-1)^n / (2n+1)! * x ^(2n+1)
 * based on previous result, in a reversed way
 *
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_sin_prev_rev (__float128 x, gint32 max_steps) {
  __float128 *array = g_malloc0 (max_steps * sizeof (__float128));
  __float128  result = 0.0Q;
        gsize i;
  
  array[0] = x;
  for (i = 1; i < max_steps; ++i)
  {
    array[i] = array[i-1] * taylor_pow (-1.0Q, i) * x * x / (2.0Q * i - 1.0Q);
  }

  for (i = max_steps - 1; i+1 > 0; --i)
  {
    result += array[i];
  }

  g_free (array);

  return result;
}

/*
 * Computes e^x
 * by calculating Taylor series formula:
 * x^k / k!
 *
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_exp (__float128 x, gint32 max_steps) {
  __float128 result = 0.0Q;
       gsize i;

  for (i = 0; i < max_steps; ++i)
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
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_exp_rev (__float128 x, gint32 max_steps) {
  __float128 *array = g_malloc0 (max_steps * sizeof (__float128));
  __float128  result = 0.0Q;
        gsize i;
  
  for (i = 0; i < max_steps; ++i)
  {
    array[i] = (__float128)(taylor_pow (x, i) / taylor_fac (i));
  }

  for (i = max_steps - 1; i+1 > 0; i--)
  {
    result += array[i];
  }

  g_free (array);

  return result;
}

/*
 * Computes e^x
 * by calculating Taylor series formula:
 * x^k / k!
 * based on previous result
 * 
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_exp_prev (__float128 x, gint32 max_steps) {
  __float128 result = 1.0Q;
       gsize i;

  for (i = 1; i < max_steps; ++i)
  {
    result += result * (x / i);
  }

  return result;
}

/*
 * Computes e^x
 * by calculating Taylor series formula:
 * x^k / k!
 * based on previous result, in a reversed way
 *
 * @arg    __float128 x
 * @arg    gint32     max_steps
 * @retval __float128 result
 *
 */
__float128
taylor_exp_prev_rev (__float128 x, gint32 max_steps) {
  __float128 *array = g_malloc0 (max_steps * sizeof (__float128));
  __float128  result = 1.0Q;
        gsize i;
  
  array[0] = 1.0Q;
  for (i = 1; i < max_steps; ++i)
  {
    array[i] = array[i-1] * (x / i);
  }

  for (i = max_steps - 1; i+1 > 0; i--)
  {
    result += array[i];
  }

  g_free (array);

  return result;
}