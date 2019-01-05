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
#include "protocols.hh"
#include "gauss.hh"

using namespace std;

int main (int argc, char *argv[])
{
  int matrix_size = 0;

  // Declaration of vectors and matrices
  double *vec_empty_GAUSS ();
  double *vec_empty_JACOBIAN ();
  double *vec_empty_GAUSS_SEIDEL ();

  double *vec_result_GAUSS ();
  double *vec_result_JACOBIAN ();
  double *vec_result_GAUSS_SEIDEL ();

  MyMatrix<double> *mat_GAUSS (matrix_size);
  MyMatrix<double> *mat_JACOBIAN (matrix_size);
  MyMatrix<double> *mat_GAUSS_SEIDEL (matrix_size);


  return EXIT_SUCCESS;
}
