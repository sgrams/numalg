/*
 *  This file is part of 04-approximations task.
 * 
 *  src/matrix.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef APPROXIMATIONS_SPARSE_MATRIX_HH
#define APPROXIMATIONS_SPARSE_MATRIX_HH
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <eigen3/Eigen/Sparse>
using namespace std;

template <class T>
class MySparseMatrix {
  public:
    int width;
    Eigen::SparseMatrix<T> matrix;
    Eigen::VectorXd<T>     vector;

    MySparseMatrix (Eigen::SparseMatrix<T> matrix, Eigen::VectorXd vector, int width)
    {
      this->matrix = matrix;
      this->vector = vector;
      this->width  = width;
    }

    Eigen::VectorXd
    sparse_LU () {
      Eigen::VectorXd ret_vec (this->width);
      Eigen::SparseLU<Eigen::SparseMatrix<T> > solver;

      // analyze mat_A and solve the system of equations
      mat_A.makeCompressed ();
      solver.analyzePattern (this->matrix);
      solver.factorize (this->matrix);
      ret_vec = solver.solve (this->vector);

      return ret_vec;
    }
};
#endif // APPROXIMATIONS_SPARSE_MATRIX_HH