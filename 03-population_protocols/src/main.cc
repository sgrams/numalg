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

#define DEFAULT_ERRORS_CSV_FILENAME     "errors.csv"
#define DEFAULT_ITERATIVE_CSV_FILENAME  "iterative.csv"
#define DEFAULT_PRECISIONS_CSV_FILENAME "precisions.csv"
#define DEFAULT_MONTECARLO_CSV_FILENAME "montecarlo.csv"

#define DEFAULT_MONTECARLO_ITERATIONS 10000 // 10k
#define DEFAULT_MIN_VALIDATION_ITERATIONS 10
#define DEFAULT_MAX_VALIDATION_ITERATIONS 10000 // 1mln
#define DEFAULT_VALIDATION_ITERATIONS_STEP 10
#define DEFAULT_JACOBI_ITERATIONS     1000 //  1k
#define DEFAULT_JACOBI_EPSILON        0.00000000000001 // 10^-14
#define DEFAULT_SEIDEL_ITERATIONS     1000 //  1k
#define DEFAULT_SEIDEL_EPSILON        0.00000000000001 // 10^-14
#define DEFUALT_MIN_ITERATIONS        1
#define DEFAULT_MAX_ITERATIONS        1000
#define DEFAULT_ITERATIONS_STEP       10
#define DEFAULT_MIN_AGENT_COUNT       3
#define DEFAULT_MAX_AGENTS_COUNT      20
#define DEFAULT_VALIDATION_AGENTS_COUNT 5

using namespace std;

/*
 * Runs all methods with fixed precision/iterations
 * and saves output to DEFAULT_ERRORS_CSV_FILENAME
*/
void run_all_methods ()
{
  MyMatrix<double> *matrix;
  MonteCarlo *monte_carlo;
  Generator  *generator;
  Result     *result;
  std::vector<Result> errors_vec;

  int size = 0;

  double *ret_vec_gaussian;
  double *ret_vec_gaussian_improved;
  double *ret_vec_seidel_approx;
  double *ret_vec_seidel_iterative;
  double *ret_vec_jacobi_approx;
  double *ret_vec_jacobi_iterative;

  for (int n = DEFAULT_MIN_AGENT_COUNT; n <= (int)DEFAULT_MAX_AGENTS_COUNT; n++)
  {
    clock_t begin_montecarlo_time = clock ();
    monte_carlo = new MonteCarlo (DEFAULT_MONTECARLO_ITERATIONS, n);
    clock_t end_montecarlo_time = clock ();
    double  diff_montecarlo_time  = (double)(end_montecarlo_time - begin_montecarlo_time) / CLOCKS_PER_SEC;

    generator   = new Generator  (n);
    matrix      = new MyMatrix<double>(generator->get_cases_count (), generator->get_matrix (), generator->get_matrix_vector ());
    size        = (n + 1) * (n + 2) / 2;
    result      = new Result ();

    // Run gaussian method
    clock_t begin_gaussian_time = clock ();
    ret_vec_gaussian            = matrix->gaussian ();
    clock_t end_gaussian_time   = clock ();
    double  diff_gaussian_time  = (double)(end_gaussian_time - begin_gaussian_time) / CLOCKS_PER_SEC;
    
    // Run gaussian improved method
    clock_t begin_gaussian_improved_time = clock ();
    ret_vec_gaussian_improved            = matrix->gaussian_improved ();
    clock_t end_gaussian_improved_time   = clock ();
    double  diff_gaussian_improved_time  = (double)(end_gaussian_improved_time - begin_gaussian_improved_time) / CLOCKS_PER_SEC;

    // Run seidel approx method
    clock_t begin_seidel_approx_time = clock ();
    ret_vec_seidel_approx = matrix->gauss_seidel_approx (DEFAULT_SEIDEL_EPSILON);
    clock_t end_seidel_approx_time   = clock ();
    double  diff_seidel_approx_time  = (double)(end_seidel_approx_time - begin_seidel_approx_time) / CLOCKS_PER_SEC;
    
    // Run jacobi approx method
    clock_t begin_jacobi_approx_time = clock ();
    ret_vec_jacobi_approx = matrix->jacobi_approx (DEFAULT_JACOBI_EPSILON);
    clock_t end_jacobi_approx_time   = clock ();
    double  diff_jacobi_approx_time  = (double)(end_jacobi_approx_time - begin_jacobi_approx_time) / CLOCKS_PER_SEC;

    // Run seidel iterative method
    clock_t begin_seidel_time = clock ();
    ret_vec_seidel_iterative = matrix->gauss_seidel_iterative (DEFAULT_SEIDEL_ITERATIONS);
    clock_t end_seidel_time   = clock ();
    double  diff_seidel_time  = (double)(end_seidel_time - begin_seidel_time) / CLOCKS_PER_SEC;

    // Run jacobi iterative method
    clock_t begin_jacobi_time = clock ();
    ret_vec_jacobi_iterative  = matrix->jacobi_iterative (DEFAULT_JACOBI_ITERATIONS);
    clock_t end_jacobi_time   = clock ();
    double  diff_jacobi_time  = (double)(end_jacobi_time - begin_jacobi_time) / CLOCKS_PER_SEC;


    // Set Gaussian elim. values
    result->agent_count  = n;
    result->abs_err_g    = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_gaussian, size);
    result->abs_err_gi   = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_gaussian_improved, size);
    result->time_g    = diff_gaussian_time;
    result->time_gi   = diff_gaussian_improved_time;

    // Set Gauss Seidel values
    result->abs_err_gs   = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_seidel_approx, size);
    result->abs_err_gsit = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_seidel_iterative, size);
    result->time_gs   = diff_seidel_approx_time;
    result->time_gsit = diff_seidel_time;

    // Set Jacobi values
    result->abs_err_j   = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_jacobi_approx, size);
    result->abs_err_jit = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_jacobi_iterative, size);
    result->time_j      = diff_jacobi_approx_time;
    result->time_jit    = diff_jacobi_time;

    // Set Monte Carlo timing
    result->time_mc   = diff_montecarlo_time;

    errors_vec.push_back (*result);
    delete matrix;
    delete generator;
    delete monte_carlo;
    delete result;

    delete[] ret_vec_gaussian;
    delete[] ret_vec_gaussian_improved;
    delete[] ret_vec_seidel_approx;
    delete[] ret_vec_seidel_iterative;
    delete[] ret_vec_jacobi_approx;
    delete[] ret_vec_jacobi_iterative;
  }
  Util::save_errors_vec_to_file (errors_vec, DEFAULT_ERRORS_CSV_FILENAME);
  errors_vec.clear();
}

/*
 * Runs iterative methods with different iterations value
 * and saves output to DEFAULT_ITERATIVE_CSV_FILENAME
*/
void run_iterative_methods_only ()
{
  MyMatrix<double> *matrix;
  MonteCarlo *monte_carlo;
  Generator  *generator;
  Result     *result;
  std::vector<Result> iterative_vec;

  int size = 0;

  double *ret_vec_jacobi_iterative;
  double *ret_vec_seidel_iterative;

  for (int n = DEFAULT_MIN_AGENT_COUNT; n <= (int)DEFAULT_MAX_AGENTS_COUNT; n++)
  {
    generator   = new Generator  (n);
    matrix      = new MyMatrix<double>(generator->get_cases_count (), generator->get_matrix (), generator->get_matrix_vector ());
    size        = (n + 1) * (n + 2) / 2;
    // Run MonteCarlo iterative method
    clock_t begin_montecarlo_time = clock ();
    monte_carlo = new MonteCarlo (DEFAULT_MONTECARLO_ITERATIONS, n);
    clock_t end_montecarlo_time = clock ();
    double  diff_montecarlo_time  = (double)(end_montecarlo_time - begin_montecarlo_time) / CLOCKS_PER_SEC;

    for (int iterations = DEFUALT_MIN_ITERATIONS; iterations <= DEFAULT_MAX_ITERATIONS; iterations += DEFAULT_ITERATIONS_STEP)
    {
      result = new Result ();
      // Run jacobi iterative method
      clock_t begin_jacobi_time = clock ();
      ret_vec_jacobi_iterative  = matrix->jacobi_iterative (iterations);
      clock_t end_jacobi_time   = clock ();
      double  diff_jacobi_time  = (double)(end_jacobi_time - begin_jacobi_time) / CLOCKS_PER_SEC;

      // Run seidel iterative method
      clock_t begin_seidel_time = clock ();
      ret_vec_seidel_iterative = matrix->gauss_seidel_iterative (iterations);
      clock_t end_seidel_time   = clock ();
      double  diff_seidel_time  = (double)(end_seidel_time - begin_seidel_time) / CLOCKS_PER_SEC;

      // Set error vector with received values
      result->agent_count  = n;
      result->iterations   = iterations;
      result->abs_err_gsit = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_seidel_iterative, size);
      result->abs_err_jit  = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_jacobi_iterative, size);
      result->time_gsit = diff_seidel_time;
      result->time_jit  = diff_jacobi_time;
      result->time_mc   = diff_montecarlo_time;
      iterative_vec.push_back (*result);
      delete[] ret_vec_seidel_iterative;
      delete[] ret_vec_jacobi_iterative;
      delete result;
    }
    delete matrix;
    delete generator;
    delete monte_carlo;
  }
  Util::save_iterative_vec_to_file (iterative_vec, DEFAULT_ITERATIVE_CSV_FILENAME);
  iterative_vec.clear();
}

/*
 * Runs precision methods with different iterations value
 * and saves output to DEFAULT_IPRECISIONS_CSV_FILENAME
*/
void run_precision_methods_only ()
{
  MyMatrix<double> *matrix;
  MonteCarlo *monte_carlo;
  Generator  *generator;
  Result     *result;
  std::vector<Result> approx_vec;

  int size = 0;

  double *ret_vec_jacobi;
  double *ret_vec_seidel;

  for (int n = DEFAULT_MIN_AGENT_COUNT; n <= (int)DEFAULT_MAX_AGENTS_COUNT; n++)
  {
    clock_t begin_montecarlo_time = clock ();
    monte_carlo = new MonteCarlo (DEFAULT_MONTECARLO_ITERATIONS, n);
    clock_t end_montecarlo_time   = clock ();
    double  diff_montecarlo_time  = (double)(end_montecarlo_time - begin_montecarlo_time) / CLOCKS_PER_SEC;

    generator   = new Generator  (n);
    matrix      = new MyMatrix<double>(generator->get_cases_count (), generator->get_matrix (), generator->get_matrix_vector ());
    size        = (n + 1) * (n + 2) / 2;

    // new for needed
    for (int counter = -1; counter >= -16; counter-=1)
    {
      result = new Result ();
      double epsilon = std::pow(10, counter);

      // Run seidel approx method
      clock_t begin_seidel_time = clock ();
      ret_vec_seidel = matrix->gauss_seidel_approx (epsilon);
      clock_t end_seidel_time   = clock ();
      double  diff_seidel_time  = (double)(end_seidel_time - begin_seidel_time) / CLOCKS_PER_SEC;

      // Run jacobi approx method
      clock_t begin_jacobi_time = clock ();
      ret_vec_jacobi  = matrix->jacobi_approx (epsilon);
      clock_t end_jacobi_time   = clock ();
      double  diff_jacobi_time  = (double)(end_jacobi_time - begin_jacobi_time) / CLOCKS_PER_SEC;

      // Set error vector with received values
      result->agent_count  = n;
      result->epsilon      = epsilon;
      result->abs_err_gs = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_seidel, size);
      result->abs_err_j  = matrix->count_abs_error (monte_carlo->get_result_vector (), ret_vec_jacobi, size);
      result->time_gs = diff_seidel_time;
      result->time_j  = diff_jacobi_time;
      result->time_mc = diff_montecarlo_time;
      approx_vec.push_back (*result);
      delete[] ret_vec_seidel;
      delete[] ret_vec_jacobi;
      delete result;
    }
    delete matrix;
    delete generator;
    delete monte_carlo;
  }
  Util::save_approx_vec_to_file (approx_vec, DEFAULT_PRECISIONS_CSV_FILENAME);
  approx_vec.clear();
}

void
run_montecarlo_validation ()
{
  MyMatrix<double> *matrix;
  MonteCarlo *monte_carlo;
  Generator  *generator;
  Result     *result;
  std::vector<Result> montecarlo_vec;

  double *ret_vec_gaussian_improved;
  int size = (DEFAULT_VALIDATION_AGENTS_COUNT + 1) * (DEFAULT_VALIDATION_AGENTS_COUNT + 2) / 2;

  generator = new Generator  (DEFAULT_VALIDATION_AGENTS_COUNT);
  matrix    = new MyMatrix<double>(generator->get_cases_count (), generator->get_matrix (), generator->get_matrix_vector ());

  for (int i = DEFAULT_MIN_VALIDATION_ITERATIONS; i < DEFAULT_MAX_VALIDATION_ITERATIONS; i += DEFAULT_VALIDATION_ITERATIONS_STEP)
  {
    result = new Result ();
    clock_t begin_montecarlo_time = clock ();
    monte_carlo = new MonteCarlo (i, DEFAULT_VALIDATION_AGENTS_COUNT);
    clock_t end_montecarlo_time   = clock ();
    double  diff_montecarlo_time  = (double)(end_montecarlo_time - begin_montecarlo_time) / CLOCKS_PER_SEC;

    // Run gaussian improved method
    clock_t begin_gaussian_improved_time = clock ();
    ret_vec_gaussian_improved            = matrix->gaussian_improved ();
    clock_t end_gaussian_improved_time   = clock ();
    double  diff_gaussian_improved_time  = (double)(end_gaussian_improved_time - begin_gaussian_improved_time) / CLOCKS_PER_SEC;

    result->iterations = i;
    result->agent_count  = DEFAULT_VALIDATION_AGENTS_COUNT;
    result->abs_err_gi   = matrix->count_error (monte_carlo->get_result_vector (), ret_vec_gaussian_improved, size);
    result->time_gi   = diff_gaussian_improved_time;
    result->time_mc   = diff_montecarlo_time;

    montecarlo_vec.push_back (*result);
    delete monte_carlo;
    delete result;
    delete[] ret_vec_gaussian_improved;
  }
  Util::save_montecarlo_vec_to_file (montecarlo_vec, DEFAULT_MONTECARLO_CSV_FILENAME);
}

int main (int argc, char *argv[])
{
  run_all_methods ();
  run_precision_methods_only ();
  run_iterative_methods_only ();
  run_montecarlo_validation ();
  return EXIT_SUCCESS;
}
