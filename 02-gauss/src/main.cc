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

  cout << "Primal Matrix" << endl;
  matrix->print_matrix ();
  cout << endl << endl << "Primal Vector X" << endl;
  matrix->print_vector_X ();
  cout << endl << endl << "Primal Vector B" << endl;
  matrix->print_vector_B ();
  cout << endl << endl << "Vector X after Gauss" << endl;
  matrix->gaussian_no_pivoting ();
  cout << endl << endl;




/*
  matrix->print_matrix ();
  cout << endl;

  matrix->gaussian_no_pivoting ();
  matrix->print_matrix ();

  

  
  cout << endl;
  matrix->print_vector_B ();
  */

  delete matrix;
  return 0;
}
