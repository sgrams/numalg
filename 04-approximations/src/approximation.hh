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

template <class T>
class Approximation
{
  private:
    T *arguments;
    T *values;
    int polynomial;
    int size;

  public:
    Approximation (T *arguments, T *values, int size, int polynomial)
    {
      this->arguments  = arguments;
      this->values     = values;
      this->size       = size;
      this->polynomial = polynomial + 1;
    }

    T *
    perform_operations ()
    {
      T **mat_A = new T[polynomial];
      T **mat_B = new T[size];

      // initialize matrices
      for (int i = 0; i < polynomial; ++i)
      {
        mat_A[i] = new T[size];
      }
      for (int i = 0; i < size; ++i)
      {
        mat_B[i] = new T[polynomial];
      }
      for (int i = 0; i < size; ++i)
      {
        for (int j = 0; j < polynomial; ++j)
        {
          mat_B[i][j] = std::pow (this->arguments[i], j);
          mat_A[j][i] = mat_B[i][j];
        }
      }

      T **mat_C = new T[polynomial];
      // initialize mat_C
      for (int i = 0; i < polynomial; ++i)
      {
        mat_C[i] = new T[polynomial];
        for (int j = 0; j < polynomial; ++j)
        {
          mat_C[i][j] = 0;
        }
      }

      for (int i = 0; i < polynomial ++i)
      {
        for (int j = 0; j < polynomial; ++j)
        {
          for (int k = 0; k < size; ++k)
          {
            mat_C[i][j] += mat_A[i][k] * mat_B[k][j]; 
          }
        }
      }

      T *vec_A = new T[polynomial];
      for (int i = 0; i < polynomial; ++i)
      {
        // initialize vec_A
        vec_A[i] = 0;
        for (int j = 0; j < size; ++j)
        {
          vec_A[i] += mat_A[i][j] * this->values[j];
        }
      }

      return vec_A;
    }
};
#endif // APPROXIMATION_APPROXIMATION_H