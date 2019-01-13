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
#include <cmath>
#include <random>
#include <algorithm>
#include <eigen3/Eigen/Sparse>
using namespace std;

template <class T>
class MySparseMatrix {
  public:
    int width;
    Eigen::SparseMatrix<T> *matrix;
    Eigen::SparseVector<T> *vector;

    MySparseMatrix (int width, Eigen::SparseMatrix<T> *matrix, Eigen::SparseVector<T> *vector)
    {
      this->matrix = matrix;
      this->vector = vector;
      this->width  = width;
    }
    
    void
    copy_vector (Eigen::SparseVector<T> *to_vector, Eigen::SparseVector<T> *from_vector, int width)
    {
      for (int i = 0; i < width; ++i)
      {
        if (from_vector->coeffRef (i) != 0) {
          to_vector->coeffRef (i) = from_vector->coeffRef (i);
        }
      }
    }

    double
    vector_norm (Eigen::SparseVector<T> *ret_vec, Eigen::SparseVector<T> *tmp_vec, int width)
    {
      double norm_1 = (double) ret_vec->squaredNorm ();
      double norm_2 = (double) tmp_vec->squaredNorm ();

      return (double) fabs (norm_1 - norm_2);
    }

    Eigen::VectorXd
    sparse_LU ()
    {
      Eigen::SparseVector<T> ret_vec;
      Eigen::SparseLU<Eigen::SparseMatrix<T> > solver;

      // analyze matrix and solve the system of equations
      this->matrix->makeCompressed ();
      solver.analyzePattern (*this->matrix);
      solver.factorize (*this->matrix);
      ret_vec = solver.solve (*this->vector);

      return ret_vec;
    }

    Eigen::VectorXd
    sparse_GS_approx (double eps)
    {
      Eigen::SparseMatrix<T> *A = this->matrix;
      Eigen::SparseVector<T> *b = this->vector;

      Eigen::SparseVector<T> ret_vec (this->width);
      Eigen::SparseVector<T> pre_vec (this->width);

      double result;
      //A->makeCompressed ();

      do {
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec.coeffRef (i) = b->coeffRef (i);
          for (int j = 0; j < i; ++j)
          {
            ret_vec.coeffRef (i) -= (pre_vec.coeffRef(j) * A->coeffRef(i, j));
          }          
          for (int j = i + 1; j < this->width; ++j)
          {
            ret_vec.coeffRef (i) -= (pre_vec.coeffRef(j) * A->coeffRef(i, j));
          }
          if (ret_vec.coeffRef (i) != 0) {
            ret_vec.coeffRef (i) /= A->coeffRef (i, i);
          }
        }


        result = vector_norm (&ret_vec, &pre_vec, this->width);
        copy_vector (&pre_vec, &ret_vec, this->width);
      } while (result > eps);

      return ret_vec;
    }

    Eigen::VectorXd
    sparse_GS (int iterations)
    {
      Eigen::SparseMatrix<T> *A = this->matrix;
      Eigen::SparseVector<T> *b = this->vector;

      Eigen::SparseVector<T> ret_vec (this->width);
      Eigen::SparseVector<T> pre_vec (this->width);

      int iterator = iterations;
      A->makeCompressed ();

      do {
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec.coeffRef (i) = b->coeffRef (i);
          for (int j = 0; j < i; ++j)
          {
            ret_vec.coeffRef (i) -= (pre_vec.coeffRef(j) * A->coeffRef(i, j));
          }          
          for (int j = i + 1; j < this->width; ++j)
          {
            ret_vec.coeffRef (i) -= (pre_vec.coeffRef(j) * A->coeffRef(i, j));
          }
          if (ret_vec.coeffRef (i) != 0) {
            ret_vec.coeffRef (i) /= A->coeffRef (i, i);
          }
        }

        iterator--;
        copy_vector (&pre_vec, &ret_vec, this->width);
      } while (iterator > 0);

      return ret_vec;
    }
};
#endif // APPROXIMATIONS_SPARSE_MATRIX_HH