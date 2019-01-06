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
using namespace std;

int main (int argc, char *argv[])
{
  Generator *g = new Generator (19);
  MyMatrix<double> *matrix = new MyMatrix<double>(g->get_cases_count (), g->get_matrix (), g->get_matrix_vector ());

  /*
  for (int i = 0; i < g->get_cases_count(); ++i)
  {
    for (int j = 0; j < g->get_cases_count(); ++j)
    {
      cout << matrix->get_matrix()[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl << endl << endl;
  */

  double *ret_vec_gaussian = matrix->gaussian ();
  double *ret_vec_jacobi_iterative = matrix->jacobi_iterative (10);
  double *ret_vec_jacobi_approx = matrix->jacobi_approx(0.01);
  double *ret_vec_seidel_iterative = matrix->gauss_seidel_iterative (10);
  double *ret_vec_seidel_approx = matrix->gauss_seidel_approx (0.01);

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

  delete matrix;
  delete g;
  delete[] ret_vec_gaussian;
  delete[] ret_vec_jacobi_iterative;
  delete[] ret_vec_jacobi_approx;
  delete[] ret_vec_seidel_iterative;
  delete[] ret_vec_seidel_approx;
  return EXIT_SUCCESS;
}
