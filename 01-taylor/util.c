/*
 *  This file is part of 01-taylor task.
 *
 *  util.c
 *  Stanisław Grams
 */
#include "util.h"
#include "taylor.h"

/*
 * Saves calculations
 * to a given file
 * 
 * @arg          FILE  *file
 * @arg    __float128 **array
 * @arg    __float128   interval_min
 * @arg    __float128   step_size
 * @arg        gint32   max_elements
 *
 */
void
util_save_array
(FILE *file, __float128 **array, __float128 interval_min,
__float128 step_size, gint32 max_elements) {
  __float128   numb = interval_min;
  gint32       i;
  gchar       *str_1;
  gchar       *str_2;
  gchar       *str_3;
  gchar       *str_4;
  gchar       *str_5;
  gchar       *str_6;

  for (i = 0; i < max_elements; numb += step_size, i++)
  {
    str_1 = taylor_print (numb);                             // (1)  x
    str_2 = taylor_print (array[0][i]);                      // (2)  e^sinx (func0)
    str_3 = taylor_print (array[1][i]);                      // (3)  e^sinx (func1)
    str_4 = taylor_print (array[2][i]);                      // (4)  e^sinx (func2)
    str_5 = taylor_print (array[3][i]);                      // (6)  e^sinx (func3)
    str_6 = taylor_print (array[4][i]);                      // (7)  e^sinx (func4)

    fprintf (file, "%s,%s,%s,%s,%s,%s\n",
      str_1, str_2, str_3,
      str_4, str_5, str_6
      );
    if (i % 10000 == 0) {
      util_print_progressbar ((gint32) (((__float128)i / (__float128)max_elements)*100.0f));
    }
    g_free (str_1);
    g_free (str_2);
    g_free (str_3);
    g_free (str_4);
    g_free (str_5);
    g_free (str_6);
  }
  util_print_progressbar (100);
  printf ("\n");
}

/*
 * Prints help
 */
void
util_print_help () {
  fprintf (stdout, "Usage: taylor -hsvia -m [4/8/16/32/64/128/256]\n");
}

/*
 * Prints a progressbar
 * 
 * @arg        gint32   percentage
 *
 */
void
util_print_progressbar
(gint32 percentage) {
  gint32 left_padding  = (gint32)((__float128) percentage/100.0f * (__float128)PROGRESSBAR_WIDTH);
  gint32 right_padding = PROGRESSBAR_WIDTH - left_padding;

  fprintf (stdout, "\r%3d%% [%.*s%*s]", percentage, left_padding, PROGRESSBAR_STRING, right_padding, "");
  fflush  (stdout);
}