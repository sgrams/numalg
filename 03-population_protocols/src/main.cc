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
  Generator *g = new Generator (5);
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
  double *ret_vec = matrix->jacobi_iterative(10);
  for (int i = 0; i < g->get_cases_count (); ++i)
  {
    cout << ret_vec[i] << ",";
  }
  cout << endl;
  delete matrix;
  delete g;
  delete[] ret_vec;
  return EXIT_SUCCESS;
}
