/*
 * This file is part of 03-population_protocol task.
 *
 * src/main.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "generator.hh"
#include "probability.hh"

#define  MAX_AGENTS_COUNT  10
#define  START_AGENT_COUNT 4
#define  ITERATIONS 10
#define  EPS 0.001
#define  DEFAULT_ERRORS_CSV_FILENAME "errors.csv"
#define  DEFAULT_SPARSE_TIMINGS_CSV_FILENAME "timings.csv"
#define  DEFAULT_ITERATION_METHODS_ERRORS_FILENAME "iterative.csv"
using namespace std;

int main (int argc, char *argv[])
{

  vector<double> ret_vec_mc;
  vector<result_fields_t> result_vec;

  double *ret_vec_gaussian;
  double *ret_vec_gaussiani;
  double *ret_vec_jacobi_iterative;
  double *ret_vec_jacobi_approx;
  double *ret_vec_seidel_iterative;
  double *ret_vec_seidel_approx;

  for(int size = START_AGENT_COUNT; size <= MAX_AGENTS_COUNT; ++size)
  {
    result_fields_t result;
    result.agent_count    = size;
    result.abs_err_g      = 0;
    result.abs_err_gi     = 0;
    result.abs_err_gs     = 0;
    result.abs_err_gsit   = 0;
    result.abs_err_j      = 0;
    result.abs_err_jit    = 0;
    result.abs_err_jit    = 0;

    for(int i = START_AGENT_COUNT; i <= MAX_AGENTS_COUNT; ++i)
      {

        Generator *g = new Generator (i);
        MyMatrix<double> *matrix = new MyMatrix<double>(g->get_cases_count (), g->get_matrix (), g->get_matrix_vector ());

        MonteCarlo *mc = new MonteCarlo (ITERATIONS, i);
  
        int size = (result.agent_count + 1) * (result.agent_count + 2);

        ret_vec_mc = mc->get_result_vector ();
        double *tab = new double[ret_vec_mc.size()];

          for (int i = 0; i < (int) ret_vec_mc.size(); ++i)
            {
              tab[i]=ret_vec_mc[i];
            }
  
        ret_vec_gaussian = matrix->gaussian ();
        ret_vec_gaussiani = matrix->gaussian_improved ();
        ret_vec_jacobi_iterative = matrix->jacobi_iterative (ITERATIONS);
        ret_vec_jacobi_approx = matrix->jacobi_approx(EPS);
        ret_vec_seidel_iterative = matrix->gauss_seidel_iterative (ITERATIONS);
        ret_vec_seidel_approx = matrix->gauss_seidel_approx (EPS);

        result.abs_err_g    = matrix->count_abs_error (tab, ret_vec_gaussian, size);
        result.abs_err_gi   = matrix->count_abs_error (tab, ret_vec_gaussiani, size);
        result.abs_err_gs   = matrix->count_abs_error (tab, ret_vec_seidel_approx, size);
        result.abs_err_gsit = matrix->count_abs_error (tab, ret_vec_seidel_iterative, size);
        result.abs_err_j    = matrix->count_abs_error (tab, ret_vec_jacobi_approx, size);
        result.abs_err_jit  = matrix->count_abs_error (tab, ret_vec_jacobi_iterative, size);
      }
      result_vec.push_back (result);
    }

    Util::save_result_vec_to_file (result_vec, DEFAULT_ERRORS_CSV_FILENAME);
    result_vec.clear ();



  delete[] ret_vec_gaussian;
  delete[] ret_vec_jacobi_iterative;
  delete[] ret_vec_jacobi_approx;
  delete[] ret_vec_seidel_iterative;
  delete[] ret_vec_seidel_approx;

  return EXIT_SUCCESS;
}
