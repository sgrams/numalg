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

#define  MAX_AGENTS_COUNT  50
#define  START_AGENT_COUNT 3
#define  DEFAULT_ERRORS_CSV_FILENAME "errors.csv"
#define  DEFAULT_SPARSE_TIMINGS_CSV_FILENAME "timings.csv"
#define  DEFAULT_ITERATION_METHODS_ERRORS_FILENAME "iterative.csv"
using namespace std;

int main (int argc, char *argv[])
{
  Generator *g = new Generator (3);
  MyMatrix<double> *matrix = new MyMatrix<double>(g->get_cases_count (), g->get_matrix (), g->get_matrix_vector ());

  MonteCarlo *mc = new MonteCarlo (1000, 3);
  
  result_fields_t result;
  result.agent_count = 3;
  int size = (result.agent_count + 1) * (result.agent_count + 2);

  vector<double> ret_vec_mc = mc->get_result_vector ();
  int a = (int)ret_vec_mc.size();
  double tab[a];
  for (int i = 0; i < (int)ret_vec_mc.size(); ++i)
  {
    tab[i]=ret_vec_mc[i];
  }
  cout << endl;

  double *ret_vec_gaussian = matrix->gaussian ();
  double *ret_vec_gaussiani = matrix->gaussian_improved ();
  double *ret_vec_jacobi_iterative = matrix->jacobi_iterative (1000);
  double *ret_vec_jacobi_approx = matrix->jacobi_approx(0.001);
  double *ret_vec_seidel_iterative = matrix->gauss_seidel_iterative (100000);
  double *ret_vec_seidel_approx = matrix->gauss_seidel_approx (0.00001);

  result.abs_err_g    += matrix->count_abs_error (tab, ret_vec_gaussian, size);
  result.abs_err_gi   += matrix->count_abs_error (tab, ret_vec_gaussiani, size);
  result.abs_err_gs   += matrix->count_abs_error (tab, ret_vec_seidel_approx, size);
  result.abs_err_gsit += matrix->count_abs_error (tab, ret_vec_seidel_iterative, size);
  result.abs_err_j    += matrix->count_abs_error (tab, ret_vec_jacobi_approx, size);
  result.abs_err_jit  += matrix->count_abs_error (tab, ret_vec_jacobi_iterative, size);
  //result.abs_err_mc   += matrix->count_abs_error (tab, ret_vec_gaussian, size);

  vector<result_fields_t> result_vec;
  result_vec.push_back (result);
  Util::save_result_vec_to_file (result_vec, "testing.csv");

  for (int i = 0; i < (int)ret_vec_mc.size(); ++i)
  {
    cout << ret_vec_mc[i] << ",";
  }
  cout << endl;

  cout << ret_vec_mc.size() << endl;

  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec_gaussian[i] << ",";
  }
  cout << endl;
  cout << endl;

  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec_jacobi_iterative[i] << ",";
  }
  cout << endl;
  cout << endl;

  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec_jacobi_approx[i] << ",";
  }
  cout << endl;
  cout << endl;

  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec_seidel_iterative[i] << ",";
  }

  cout << endl;
  cout << endl;

  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec_seidel_approx[i] << ",";
  }
  
  cout << endl;

  delete mc;
  delete matrix;
  delete g;
  
  delete[] ret_vec_gaussian;
  delete[] ret_vec_jacobi_iterative;
  delete[] ret_vec_jacobi_approx;
  delete[] ret_vec_seidel_iterative;
  delete[] ret_vec_seidel_approx;

  return EXIT_SUCCESS;
}
