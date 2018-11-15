#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#include "gauss.hh"
using namespace std;

int main (int argc, char *argv[]) {
  
  MyMatrix<float>* matrix = new MyMatrix<float>(3);

  matrix->fill_matrix ();
  matrix->fill_vector_X ();
  matrix->fill_vector_B ();

  matrix->print_matrix ();
  cout << endl;
  matrix->print_vector_X ();
  cout << endl;
  matrix->print_vector_B ();
  
  delete matrix;
  return 0;
}
