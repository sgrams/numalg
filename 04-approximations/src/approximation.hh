/*
 *  This file is part of 04-approximation task.
 * 
 *  src/approximation.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef APPROXIMATION_APPROXIMATION_H
#define APPROXIMATION_APPROXIMATION_H

#include "matrix.hh"

template <class T>
class Approximation
{
  private:
    T *arguments;
    T *values;
    int size;
    int polynomial;

  public:
    Approximation (T *arguments, T *values, int size, int polynomial)
    {
      this->arguments  = arguments;
      this->values     = values;
      this->polynomial = polynomial;
      this->size       = size;
    }

    T *
    perform_operations ()
    {
      int degree_A = 2 * polynomial + 1;
      int degree_B = polynomial + 1;

      T **coeff_A = new T*[size];
      T **coeff_B = new T*[size];
      T *vec_A    = new T[degree_A];
      T *vec_B    = new T[degree_B];
      
      // matrix and vectors initialization
      for (int i = 0; i < size; ++i)
      {
        coeff_A[i] = new T[degree_A];
        coeff_B[i] = new T[degree_B];
      }

      for (int i = 0; i < degree_A; ++i)
      {
        vec_A[i] = 0;
      }

      for (int i = 0; i < degree_B; ++i)
      {
        vec_B[i] = 0;
      }

      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < degree_A; ++j)
        {
          coeff_A[i][j] = std::pow (this->arguments[i], j);
          vec_A[j]     += coeff_A[i][j];
        }
      }

      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < degree_B; ++j)
        {
          coeff_B[i][j] = this->values[i] * coeff_A[i][j];
          vec_B[j]     += coeff_B[i][j];
        }
      }
      
      T **result_matrix = new T*[degree_B];
      T *result_vec     = new T[degree_B];

      for (int i = 0; i < degree_B; ++i)
      {
        result_matrix[i] = new T[degree_B];
        result_vec[i]    = 0;
      }

      int iter = 0;
      for (int i = 0; i < degree_B; ++i)
      {
        for (int j = 0; j <degree_B; ++j)
        {
          result_matrix[i][j] = vec_A[j+iter];
        }
        result_vec[i] = vec_B[i];
        iter++;
      }

      MyMatrix<double> *matrix = new MyMatrix<double>(degree_B, result_matrix, result_vec);
      double *ret_vec_gaussian = matrix->gaussian_improved ();
      delete matrix;

      return ret_vec_gaussian;
    }
};
#endif // APPROXIMATION_APPROXIMATION_H