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
 * @arg    int64_t n
 * @retval int64_t result
 *
 */
int64_t factorial (int64_t n) {
  int64_t i;
  int64_t result = 1;

  if (n <= 1) {
    return 1;
  }
  for (i = 1; i <= n; i++)
  {
    result *= i;
  }
  return result;
}
