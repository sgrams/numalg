/*
 *  This file is part of 01-taylor task.
 * 
 *  main.c
 *  Stanisław Grams
 */
#include <stdio.h>
#include <glib.h>
#include <quadmath.h>
#include <pthread.h>
#include "taylor.h"

/*
 * Calculate and write to buffer
 * first function (taylor_func0)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval     gint32

/*
 * Entrypoint of the program
 *
 * @arg    gint32   argc
 * @arg    gchar  **argv
 * @retval gint32
 *
 */
gint32 main (gint32 argc, gchar **argv) {
  gint32      i;
//gchar      *str;
  __float128 *array;
//__float128  numb;
  __float128  iter;

/*
  numb = taylor_func0 (5.00000000000000000000000000000001Q);
  str = taylor_print (numb);
  printf ("%s\n", str);
  free (str);
*/
  array = g_malloc0 (30000000 * sizeof (__float128));
  for (i = 0, iter = INTERVAL_MIN; iter < INTERVAL_MAX-Q_SUM_STEP; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func0 (iter);
  }

  g_free (array);

  return 0;
}