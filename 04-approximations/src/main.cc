/*
 * This file is part of 04-approximations task.
 *
 * src/main.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 * Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "sparsematrix.hh"
#include "generator.hh"
#include "sparsegenerator.hh"
#include "probability.hh"

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
#define DEFAULT_ARGUMENTS_LENGTH      10

using namespace std;

int main (int argc, char *argv[])
{
  //Approximation *ap = new Approximation( );
  SparseGenerator<double> sg = SparseGenerator<double>(50);
  MySparseMatrix<double> *sparsematrix = new MySparseMatrix<double>(sg.get_cases_count (), sg.get_matrix (), sg.get_matrix_vector ());
  clock_t begin_sparse_LU_time = clock ();
  Eigen::VectorXd ret_vec = sparsematrix->sparse_LU ();
  clock_t end_sparse_LU_time = clock ();
  double  diff_sparse_LU_time  = (double)(end_sparse_LU_time - begin_sparse_LU_time) / CLOCKS_PER_SEC;
  cout << diff_sparse_LU_time << endl;


  Generator g = Generator(50);
  MyMatrix<double> *matrix = new MyMatrix<double>(g.get_cases_count (), g.get_matrix (), g.get_matrix_vector ());
  clock_t begin_gaussian_sparse_time = clock ();
  double *gaussian_ret_vec = matrix->gaussian_improved ();
  clock_t end_gaussian_sparse_time = clock ();
  double  diff_gaussian_sparse_time = (double)(end_gaussian_sparse_time - begin_gaussian_sparse_time) / CLOCKS_PER_SEC;
  cout << diff_gaussian_sparse_time << endl;


  cout << sg.get_cases_count () << endl;
  delete sparsematrix;
  return EXIT_SUCCESS;
}