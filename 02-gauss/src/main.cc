/*
 *  This file is part of 02-gauss task.
 * 
 *  src/main.cc
 *  Grams, Stanislaw <sgrams@fmdx.pl>
 *  Jezierski, Maciej <maciejjezierski4@gmail.com>
 *  Korczakowski, Juliusz <iuliuszkor@gmail.com>
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#include "gauss.hh"
#include "util.hh"

using namespace std;

int main (int argc, char *argv[]) {
  Util::print_help ();
  /*
  MyMatrix<MyType>* matrix = new MyMatrix<MyType>(10);
  MyType *ret_vec;
  matrix->fill_matrix ();
  matrix->fill_vector_X ();
  matrix->fill_vector_B ();

  cout << "Primal Matrix" << endl;
  matrix->print_matrix ();
  cout << endl << endl << "Primal Vector X" << endl;
  matrix->print_vector (matrix->get_vector_B (), matrix->get_width ());
  cout << endl << endl << "Primal Vector B" << endl;
  matrix->print_vector (matrix->get_vector_X (), matrix->get_width ());
  cout << endl << endl << "Vector X after Gauss" << endl;
  
  ret_vec = matrix->gaussian_no_pivoting ();
  for (int i = 0; i < 3; ++i) {
    cout << ret_vec[i] << endl;
  }
  cout << endl << endl;
  delete[] ret_vec;

  cout << endl << endl << "Vector X after Gauss_Partial_Pivoting" << endl;
  ret_vec = matrix->gaussian_partial_pivoting ();
  for (int i = 0; i < 3; ++i) {
    cout << ret_vec[i] << endl;
  }
  cout << endl << endl;
  delete[] ret_vec;

  cout << endl << endl << "Vector X after Gauss_Complete_Pivoting" << endl;
  ret_vec = matrix->gaussian_complete_pivoting ();
  for (int i = 0; i < 3; ++i) {
    cout << ret_vec[i] << endl;
  }
  cout << endl << endl;

  delete matrix;
  delete[] ret_vec;
*/
  return 0;
}
