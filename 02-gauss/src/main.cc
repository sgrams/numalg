#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#include "gauss.hh"
using namespace std;

int main (int argc, char *argv[]) {
  
  MyMatrix<float>* matrix = new MyMatrix<float>(3);
  matrix->fill();
  matrix->print();
  float* Tab;
  Tab=matrix->gaussian_no_pivoting();
  for (int i=0; i<3; i++) cout<<Tab[i]<<endl;

  delete[] Tab;
  delete matrix;
  return 0;
}
