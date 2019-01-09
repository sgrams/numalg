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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define PROGRESSBAR_STRING "#################################################"
#define PROGRESSBAR_WIDTH  50

class Result {
  public:
    int agent_count    = 0;
    int iterations     = 0;
    double epsilon     = 0.0;
    // absolutes errors
    double abs_err_g     = 0.0;
    double abs_err_gi  = 0.0;   //gauss imporved
    double abs_err_gs  = 0.0;   //gauss-seidel
    double abs_err_gsit  = 0.0; //gauss-seidel iterative
    double abs_err_j = 0.0;     //jacobi
    double abs_err_jit = 0.0;   //jacobi iterative
    // times
    double time_g   = 0.0;
    double time_gi = 0.0;
    double time_gs = 0.0; 
    double time_gsit = 0.0;
    double time_j = 0.0;
    double time_jit = 0.0;
    double time_mc = 0.0;
};

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
  save_errors_vec_to_file (const std::vector<Result> &result_vec, std::string filename);

  void
  save_iterative_vec_to_file (const std::vector<Result> &result_vec, std::string filename);

  void
  save_approx_vec_to_file (const std::vector<Result>&result_vec, std::string filename);
  
  unsigned int
  calculate_newton (unsigned int n, unsigned int k);
}
#endif // _GAUSS_UTIL_H