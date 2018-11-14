#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#include "gauss.hh"
using namespace std;

int main (int argc, char *argv[]) {
  MyMatrix<float>*matrix = new MyMatrix<float>(10);
  
  matrix->fill();
  matrix->print();
  float* Tab = matrix->backsub();

  delete[] Tab;
  delete matrix;
  return 0;
}
