/*
 * This file is part of 01-taylor task.
 *
 * taylor.c
 * Stanisław Grams
 */
#include "taylor.h"

/*
 * Computes factorial
 *
 * @arg    gint64 n
 * @retval gint64 result
 *
 */
gint64 factorial (gint64 n) {
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
