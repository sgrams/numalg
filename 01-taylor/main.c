/*
 *  This file is part of 01-taylor task.
 * 
 *  main.c
 *  Stanisław Grams
 */
#include <stdio.h>
#include <glib.h>
#include <quadmath.h>
#include "taylor.h"
/*
 * Entrypoint of the program
 *
 * @arg    gint32   argc
 * @arg    gchar  **argv
 * @retval gint32
 *
 */
gint32 main (gint32 argc, gchar **argv) {
  gchar      *str;
  __float128  numb = taylor_func1 (2.2Q);

  str = taylor_print (numb);
  printf ("%s\n", str);

  free (str);
  return 0;
}
