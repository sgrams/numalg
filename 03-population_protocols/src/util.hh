/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/util.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef _GAUSS_UTIL_H
#define _GAUSS_UTIL_H
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define PROGRESSBAR_STRING "#################################################"
#define PROGRESSBAR_WIDTH  50

typedef struct result_fields {
  int matrix_size    = 0;
  // absolutes errors
  double abs_err     = 0.0;
  double abs_err_pg  = 0.0;
  double abs_err_fg  = 0.0;
  // relative errors
  double rel_err     = 0.0;
  double rel_err_pg  = 0.0;
  double rel_err_fg  = 0.0;
  // times
  double avg_time    = 0.0;
  double avg_time_pg = 0.0;
  double avg_time_fg = 0.0;
} result_fields_t;

typedef struct progressbar_sync {
  int cur_value = 0;
  int max_value = 0;
} progressbar_sync_t;

namespace Util {
  void
  print_help ();

  void
  print_progressbar (int percentage);

  void
  save_result_vec_to_file (const vector<result_fields_t > &result_vec, string filename);

  unsigned int
  calculate_newton (unsigned int n, unsigned int k);
}
#endif // _GAUSS_UTIL_H