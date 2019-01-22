/*
 *  This file is part of 01-taylor task.
 *
 *  util.h
 *  Stanisław Grams
 */
#ifndef UTIL_H_
#define UTIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <quadmath.h>
#include "glib.h"

#define MAX_RESULTS        6
#define PROGRESSBAR_STRING "#################################################"
#define PROGRESSBAR_WIDTH  50

void util_save_array (FILE *file, __float128 **array, __float128 interval_min, __float128 step_size, gint32 max_elements);
void util_print_help ();
void util_print_progressbar (gint32 percentage);
#endif //UTIL_H_