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
#include <unistd.h>
#include <ctype.h>
#include "taylor.h"
#include "util.h"

#define  MAX_RESULTS 6
#define  MAX_THREADS MAX_RESULTS

#define  DEFAULT_MAX_STEPS 16

#define  DEFAULT_M2_OUTPUT_FILEPATH   "output_m2.csv"
#define  DEFAULT_M4_OUTPUT_FILEPATH   "output_m4.csv"
#define  DEFAULT_M8_OUTPUT_FILEPATH   "output_m8.csv"
#define  DEFAULT_M16_OUTPUT_FILEPATH  "output_m16.csv"
#define  DEFAULT_M32_OUTPUT_FILEPATH  "output_m32.csv"
#define  DEFAULT_M64_OUTPUT_FILEPATH  "output_m64.csv"
#define  DEFAULT_M128_OUTPUT_FILEPATH "output_m128.csv"
#define  DEFAULT_M256_OUTPUT_FILEPATH "output_m256.csv"

gint32 max_steps;

/*
 * Calculate and write to buffer
 * first function (taylor_func0)
 * of a given number of elements
 * 
 * @arg    long double *buffer
 * @retval     gint32
 *
 */
void * worker_func0 (void *buffer) {
      gint32  i;
  long double  iter;
  long double *array = buffer;

  for (i = 0, iter = INTERVAL_MIN; i < MAX_ELEMENTS; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func0 (iter);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * first function (taylor_func1)
 * of a given number of elements
 * 
 * @arg    long double *buffer
 * @retval     gint32
 *
 */
void * worker_func1 (void *buffer) {
      gint32  i;
  long double  iter;
  long double *array = buffer;

  for (i = 0, iter = INTERVAL_MIN; i < MAX_ELEMENTS; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func1 (iter, max_steps);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * first function (taylor_func2)
 * of a given number of elements
 * 
 * @arg    long double *buffer
 * @retval     gint32
 *
 */
void * worker_func2 (void *buffer) {
      gint32  i;
  long double  iter;
  long double *array = buffer;

  for (i = 0, iter = INTERVAL_MIN; i < MAX_ELEMENTS; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func2 (iter, max_steps);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Entrypoint of the program
 *
 * @arg    gint32   argc
 * @arg    gchar  **argv
 * @retval gint32
 *
 */
gint32 main (gint32 argc, gchar **argv) {
  gint32        i;
  gint32        ret;
  gint32        max_steps_given;

  pthread_t     threads[MAX_THREADS];
  FILE         *output_file;
  long double  **array;

  char         c;
  char         *str_opt;
  char         *output_filepath;

  
  max_steps = DEFAULT_MAX_STEPS;

  while ((c = getopt (argc, argv, "hram:")) != -1)
  {
    switch (c)
    {
      case 'h':
        util_print_help ();
        return 0;
      case 'a':
        break;
      case 'm':
        str_opt = optarg;
        max_steps_given = g_ascii_strtoll (str_opt, NULL, 10);
        if (max_steps_given == 2) {
          output_filepath = g_strdup(DEFAULT_M2_OUTPUT_FILEPATH);
        } else if (max_steps_given == 4) {
          output_filepath = g_strdup(DEFAULT_M4_OUTPUT_FILEPATH);
        } else if (max_steps_given == 8) {
          output_filepath = g_strdup(DEFAULT_M8_OUTPUT_FILEPATH);
        } else if (max_steps_given == 16) {
          output_filepath = g_strdup(DEFAULT_M16_OUTPUT_FILEPATH);
        } else if (max_steps_given == 32) {
          output_filepath = g_strdup(DEFAULT_M32_OUTPUT_FILEPATH);
        } else if (max_steps_given == 64) {
          output_filepath = g_strdup(DEFAULT_M64_OUTPUT_FILEPATH);
        } else if (max_steps_given == 128) {
          output_filepath = g_strdup(DEFAULT_M128_OUTPUT_FILEPATH);
        } else if (max_steps_given == 256) {
          output_filepath = g_strdup(DEFAULT_M256_OUTPUT_FILEPATH);
        } else {
          fprintf (stderr,
            "Invalid number of steps given. Continuing with default m=%i\n",
            max_steps
            );
        }
        max_steps = max_steps_given;
        break;
      case '?':
        if (optopt == 'c') {
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        }
        else if (isprint (optopt)) {
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        }
        else {
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        }
        return 1;
      default:
        abort ();
    }
  }

  array = g_malloc (MAX_RESULTS * sizeof (long double *));
  for (i = 0; i < MAX_RESULTS; i++)
  {
    array[i] = g_malloc (MAX_ELEMENTS * sizeof (long double));
  }
  // Create thread for worker_func0
  ret = pthread_create (&threads[0], NULL, worker_func0, (void *)array[0]);
  if (ret) {
    fprintf (stdout, "Unable to create thread for worker_func0: %i\n", ret);
    exit (-1);
  }

  // Create thread for worker_func1
  ret = pthread_create (&threads[1], NULL, worker_func1, (void *)array[1]);
  if (ret) {
    fprintf (stdout, "Unable to create thread for worker_func1: %i\n", ret);
    exit (-1);
  }

  // Create thread for worker_func2
  ret = pthread_create (&threads[2], NULL, worker_func2, (void *)array[2]);
  if (ret) {
    fprintf (stdout, "Unable to create thread for worker_func2: %i\n", ret);
    exit (-1);
  }

  // Wait till all threads join main program
  pthread_join (threads[0], NULL);
  pthread_join (threads[1], NULL);
  pthread_join (threads[2], NULL);

  // Save calculated data to a comma-separated file
  output_file = fopen (output_filepath, "w+");
  if (output_file == NULL) {
    printf ("Unable to open file! Exiting...\n");
    return 1;
  }

  util_save_array (output_file, array);

  // Free all of array elements
  for (i = 0; i < MAX_RESULTS; i++) {
    g_free (array[i]);
  }
  fclose (output_file);

  pthread_exit (NULL);
}