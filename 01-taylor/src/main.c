/*
 *  This file is part of 01-taylor task.
 * 
 *  main.c
 *  Stanisław Grams
 */
#include <stdio.h>
#include <glib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "taylor.h"
#include "util.h"

#define  MAX_RESULTS 6
#define  MAX_THREADS MAX_RESULTS

#define  DEFAULT_M2_OUTPUT_FILEPATH   "output_m2.csv"
#define  DEFAULT_M4_OUTPUT_FILEPATH   "output_m4.csv"
#define  DEFAULT_M8_OUTPUT_FILEPATH   "output_m8.csv"
#define  DEFAULT_M16_OUTPUT_FILEPATH  "output_m16.csv"
#define  DEFAULT_M32_OUTPUT_FILEPATH  "output_m32.csv"
#define  DEFAULT_M64_OUTPUT_FILEPATH  "output_m64.csv"
#define  DEFAULT_M128_OUTPUT_FILEPATH "output_m128.csv"
#define  DEFAULT_M256_OUTPUT_FILEPATH "output_m256.csv"
#define  DEFAULT_M512_OUTPUT_FILEPATH "output_m512.csv"
#define  DEFAULT_M1024_OUTPUT_FILEPATH "output_m1024.csv"
#define  DEFAULT_M2048_OUTPUT_FILEPATH "output_m2048.csv"
#define  DEFAULT_OUTPUT_FILEPATH DEFAULT_M16_OUTPUT_FILEPATH

#define  DEFAULT_MAX_STEPS 16
#define  DEFAULT_INTERVAL_MIN -10
#define  DEFAULT_MAX_ELEMENTS 2000000
#define  DEFAULT_STEP_SIZE 0.00001Q

gint32     max_steps    = DEFAULT_MAX_STEPS;
gint32     max_elements = DEFAULT_MAX_ELEMENTS;
__float128 interval_min = DEFAULT_INTERVAL_MIN;
__float128 step_size    = DEFAULT_STEP_SIZE;

/*
 * Calculate and write to buffer
 * first function (taylor_func0)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval gint32
 *
 */
void * worker_func0 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = interval_min; i < max_elements; iter += step_size, i++)
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
 * @arg    __float128 *buffer
 * @retval gint32
 *
 */
void * worker_func1 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = interval_min; i < max_elements; iter += step_size, i++)
  {
    array[i] = taylor_func1 (taylor_optimize_arg(iter), max_steps);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * second function (taylor_func2)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval gint32
 *
 */
void * worker_func2 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = interval_min; i < max_elements; iter += step_size, i++)
  {
    array[i] = taylor_func2 (taylor_optimize_arg(iter), max_steps);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * third function (taylor_func3)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval gint32
 *
 */
void * worker_func3 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = interval_min; i < max_elements; iter += step_size, i++)
  {
    array[i] = taylor_func3 (taylor_optimize_arg(iter), max_steps);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * fourth function (taylor_func4)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval gint32
 *
 */
void * worker_func4 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = interval_min; i < max_elements; iter += step_size, i++)
  {
    array[i] = taylor_func4 (taylor_optimize_arg(iter), max_steps);
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
  gboolean     verbose_flag             = FALSE;
  gboolean     average_calculation_flag = FALSE;
  char        *average_calculation_str  = NULL;
  char        *output_filepath          = NULL;
  char         c;
  char         str_buf[MAX_BUF];

  gint32        i;
  gint32        ret;
  gint32        max_steps_given;

  __float128    average_diff;
  __float128    step_size_given;
  __float128    interval_min_given;
  __float128  **array;              // Contains the output of calculations.

  pthread_t     threads[MAX_THREADS];
  FILE         *output_file;

  while ((c = getopt (argc, argv, "hsviam:")) != -1)
  {
    switch (c)
    {
      case 'h':
        util_print_help ();
        return 0;
      case 's':
        step_size_given = strtoflt128 (optarg, NULL);
        if (step_size_given > 0) {
          step_size = step_size_given;
        }
        break;
      case 'v':
        verbose_flag = TRUE;
        break;
      case 'i':
        interval_min_given = strtoflt128 (optarg, NULL);
        interval_min = interval_min_given;
        break;
      case 'a':
        average_calculation_flag = TRUE;
        break;
      case 'm':
        max_steps_given = g_ascii_strtoll (optarg, NULL, 10);
        if (max_steps_given == 2) {
          output_filepath = g_strdup (DEFAULT_M2_OUTPUT_FILEPATH);
        } else if (max_steps_given == 4) {
          output_filepath = g_strdup (DEFAULT_M4_OUTPUT_FILEPATH);
        } else if (max_steps_given == 8) {
          output_filepath = g_strdup (DEFAULT_M8_OUTPUT_FILEPATH);
        } else if (max_steps_given == 16) {
          output_filepath = g_strdup (DEFAULT_M16_OUTPUT_FILEPATH);
        } else if (max_steps_given == 32) {
          output_filepath = g_strdup (DEFAULT_M32_OUTPUT_FILEPATH);
        } else if (max_steps_given == 64) {
          output_filepath = g_strdup (DEFAULT_M64_OUTPUT_FILEPATH);
        } else if (max_steps_given == 128) {
          output_filepath = g_strdup (DEFAULT_M128_OUTPUT_FILEPATH);
        } else if (max_steps_given == 256) {
          output_filepath = g_strdup (DEFAULT_M256_OUTPUT_FILEPATH);
        } else if (max_steps_given == 512) {
          output_filepath = g_strdup (DEFAULT_M512_OUTPUT_FILEPATH);
        } else if (max_steps_given == 1024) {
          output_filepath = g_strdup (DEFAULT_M1024_OUTPUT_FILEPATH);
        } else {
          fprintf (stderr,
            "Invalid number of steps given. Continuing with default m=%i\n",
            max_steps
            );
          break;
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

  if (output_filepath == NULL) {
    output_filepath = g_strdup (DEFAULT_OUTPUT_FILEPATH);
  }

  if (verbose_flag) {
    fprintf (stdout, "Runtime parameters:\n");

    quadmath_snprintf (str_buf, MAX_BUF * sizeof (char), "%Qf", step_size);
    fprintf (stdout, "  step_size    = %s\n", str_buf);

    quadmath_snprintf (str_buf, MAX_BUF * sizeof (char), "%Qf", interval_min);
    fprintf (stdout, "  interval_min = %s\n", str_buf);

    fprintf (stdout, "  max_elements = %i\n",   max_elements);
    fprintf (stdout, "  max_steps    = %i\n",   max_steps);
    fprintf (stdout, "  printing to %s file\n", output_filepath);
  }

  array = g_malloc (MAX_RESULTS * sizeof (__float128 *));
  for (i = 0; i < MAX_RESULTS; i++)
  {
    array[i] = g_malloc (max_elements * sizeof (__float128));
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

  // Create thread for worker_func3
  ret = pthread_create (&threads[3], NULL, worker_func2, (void *)array[3]);
  if (ret) {
    fprintf (stdout, "Unable to create thread for worker_func3: %i\n", ret);
    exit (-1);
  }

// Create thread for worker_func4
  ret = pthread_create (&threads[4], NULL, worker_func2, (void *)array[4]);
  if (ret) {
    fprintf (stdout, "Unable to create thread for worker_func4: %i\n", ret);
    exit (-1);
  }

  // Wait till all threads join main program
  fprintf (stdout, "Processing data...\n");
  util_print_progressbar (0);
  pthread_join (threads[0], NULL);
  util_print_progressbar (20);
  pthread_join (threads[1], NULL);
  util_print_progressbar (40);
  pthread_join (threads[2], NULL);
  util_print_progressbar (60);
  pthread_join (threads[3], NULL);
  util_print_progressbar (80);
  pthread_join (threads[4], NULL);
  util_print_progressbar (100);
  fprintf (stdout, "\n");

  // Save calculated data to a comma-separated file
  fprintf (stdout, "\nSaving data to %s file.\n", output_filepath);
  output_file = fopen (output_filepath, "w+");
  if (output_file == NULL) {
    printf ("Unable to open file! Exiting...\n");
    return 1;
  }
  util_save_array (output_file, array, interval_min, step_size, max_elements);

  // Perform and show average differences between
  // func1, func2, func, func4 functions
  // and results of func0
  if (average_calculation_flag) {
    average_diff = 0.0Q;
    for (i = 0; i < max_elements; ++i)
    {
      average_diff += (fabsq (array[0][i] - array[1][i]) / (__float128)(i + 1.0Q));
    }
    average_calculation_str = taylor_print (average_diff);
    fprintf (stdout, "func1() avg. absolute diff to func0() with M=%i is\n%s\n", max_steps, average_calculation_str);
    g_free (average_calculation_str);
    
    average_diff = 0.0Q;
    for (i = 0; i < max_elements; ++i)
    {
      average_diff += (fabsq (array[0][i] - array[2][i]) / (__float128)(i + 1.0Q));
    }
    average_calculation_str = taylor_print (average_diff);
    fprintf (stdout, "func2() avg. absolute diff to func0() with M=%i is\n%s\n", max_steps, average_calculation_str);
    g_free (average_calculation_str);

    average_diff = 0.0Q;
    for (i = 0; i < max_elements; ++i)
    {
      average_diff += (fabsq (array[0][i] - array[3][i]) / (__float128)(i + 1.0Q));
    }
    average_calculation_str = taylor_print (average_diff);
    fprintf (stdout, "func3() avg. absolute diff to func0() with M=%i is\n%s\n", max_steps, average_calculation_str);
    g_free (average_calculation_str);
    
    average_diff = 0.0Q;
    for (i = 0; i < max_elements; ++i)
    {
      average_diff += (fabsq (array[0][i] - array[4][i]) / (__float128)(i + 1.0Q));
    }
    average_calculation_str = taylor_print (average_diff);
    fprintf (stdout, "func4() avg. absolute diff to func0() with M=%i is\n%s\n", max_steps, average_calculation_str);
    g_free (average_calculation_str);
  }

  // Free all of array elements
  for (i = 0; i < MAX_RESULTS; i++) {
    g_free (array[i]);
  }
  g_free (array);
  g_free (output_filepath);

  fclose (output_file);
  pthread_exit (NULL);
}