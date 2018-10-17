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
 * @arg    FILE        *file
 * @arg    __float128 **array
 * @arg    __float128   interval_min
 * @arg    __float128   step_size
 * @arg    gint32       max_elements
 * @retval none
 */
void
util_save_array
(FILE *file, __float128 **array, __float128 interval_min,
__float128 step_size, gint32 max_elements) {
  __float128  numb = interval_min;
  gint32      i;
  gint32      j;
  gchar      *str_arr[MAX_RESULTS];

  for (i = 0; i < max_elements; numb += step_size, i++)
  {
    // Convert the argument (x) to gchar * and place it under str_arr[0].
    str_arr[0] = taylor_print (numb);
    // Convert results of calculations to gchar * and place it under str_arr[1..5].
    for (j = 1; j < MAX_RESULTS; ++j)
    {
      str_arr[j] = taylor_print (array [j-1][i]);
    }

    // Save output row to the output file.
    fprintf (file, "%s,%s,%s,%s,%s,%s\n",
      str_arr[0], str_arr[1], str_arr[2],
      str_arr[3], str_arr[4], str_arr[5]
      );
    
    // Refresh progressbar if the number of iterations is divisible by 10000.
    if (i % 10000 == 0) {
      util_print_progressbar ((gint32) (((__float128)i / (__float128)max_elements)*100.0f));
    }

    // Free the pointers! (uwolnić wskaźniki!)
    for (j = 0; j < MAX_RESULTS; ++j)
    {
      g_free (str_arr[j]);
    }
  }
  util_print_progressbar (100);
  printf ("\n");
}

/*
 * Prints help
 * @arg    none
 * @retval none
 * 
 */
void
util_print_help () {
  fprintf (stdout, "Usage: taylor -hsvia -m [4/8/16/32/64/128/256]\n");
}

/*
 * Prints a progressbar
 * in a nice way
 * 
 * @arg    gint32   percentage
 * @retval none
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