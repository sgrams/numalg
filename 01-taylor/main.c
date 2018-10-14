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
#include "util.h"

#define  MAX_RESULTS 6
#define  MAX_THREADS MAX_RESULTS
#define  OUTPUT_FILEPATH "output.csv"

/*
 * Calculate and write to buffer
 * first function (taylor_func0)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval     gint32
 *
 */
void * worker_func0 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

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
 * @arg    __float128 *buffer
 * @retval     gint32
 *
 */
void * worker_func1 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = INTERVAL_MIN; i < MAX_ELEMENTS; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func1 (iter);
  }
  buffer = array;

  pthread_exit (NULL);
}

/*
 * Calculate and write to buffer
 * first function (taylor_func2)
 * of a given number of elements
 * 
 * @arg    __float128 *buffer
 * @retval     gint32
 *
 */
void * worker_func2 (void *buffer) {
      gint32  i;
  __float128  iter;
  __float128 *array = buffer;

  for (i = 0, iter = INTERVAL_MIN; i < MAX_ELEMENTS; iter += Q_SUM_STEP, i++)
  {
    array[i] = taylor_func2 (iter);
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
  gint32       i;
  gint32       ret;
  pthread_t    threads[MAX_THREADS];
  __float128  **array;
  FILE        *output_file;

  array = g_malloc (MAX_RESULTS * sizeof (__float128 *));
  for (i = 0; i < MAX_RESULTS; i++)
  {
    array[i] = g_malloc (MAX_ELEMENTS * sizeof (__float128));
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
  output_file = fopen (OUTPUT_FILEPATH, "w+");
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