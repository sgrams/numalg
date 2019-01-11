/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/matrix.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef PROTOCOLS_MATRIX_HH
#define PROTOCOLS_MATRIX_HH
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include "protocol.hh"

using namespace std;

template <class T>
class MyMatrix {
  private:
    T **matrix;
    T  *vector;

    int width;
  public:
    MyMatrix (int width)
    {
      this->width    = width;
      this->matrix   = new T*[width];
      this->vector   = new T[width];

      // create a square matrix of specified width
      for (int i = 0; i < width; i++)
      {
        matrix[i] = new T[width];
      }
    }
    
    MyMatrix (int width, T** matrix_to_clone, T* vector_to_clone)
    {
      this->width    = width;
      this->matrix   = new T*[width];
      this->vector   = new T[width];

      // create a square matrix of specified width
      for (int i = 0; i < width; i++)
      {
        matrix[i] = new T[width];
        vector[i] = vector_to_clone[i];
        for (int j = 0; j < width; ++j)
        {
          matrix[i][j] = matrix_to_clone[i][j];
        }
      }
    }

    ~MyMatrix ()
    {
      for (int i = 0; i < this->width; i++)
      {
        delete[] this->matrix[i];
      }
      delete[] this->matrix;
      delete[] this->vector;
    }

    // getters
    int
    get_width ()
    {
      return this->width;
    };
    T
    **get_matrix ()
    {
      return this->matrix;
    };
    T
    *get_vector ()
    {
      return this->vector;
    };

    // setters
    void
    set_vector (T *vector)
    {
      this->vector = vector;
    }
    void set_matrix (T **matrix)
    {
      this->matrix = matrix;
    }

    // i/o streams operations
    void
    print_matrix ()
    {
      for (int i = 0; i < width; ++i)
      {
        for (int j = 0; j < width; ++j)
        {
          cout << matrix[i][j] << " ";
          if (j == width - 1) {
            cout << endl;
          }
        }
      }
    }

    // cloning methods for gaussian elimination methods
    T
    **clone_matrix (T **matrix, int width)
    {
      T **A = new T*[width];

      for (int i = 0; i < width; ++i)
      {
        A[i] = new T[width];
        for (int j = 0; j < width; ++j)
        {
          A[i][j] = matrix[i][j];
        }
      }

      return A;
    }

    T
    *clone_vector (T *vector, int width)
    {
      T *b = new T[width];
      for (int i = 0; i < width; ++i)
      {
        b[i] = vector[i];
      }

      return b;
    }

    // delete methods for gaussian elimination methods
    void
    delete_matrix (T **matrix, int width)
    {
      for (int i = 0; i < width; ++i) {
        delete[] matrix[i];
      }
      delete[] matrix;
      return;
    }

    void
    delete_vector (T *vector)
    {
      delete[] vector;
      return;
    }
    
    double vector_norm (T* ret_vec, T* tmp_vec, int width)
    {
      double result  = 0.0;
      double helper;
      for (int i = 0; i < width; ++i)
      {
        helper  = fabs(ret_vec[i] - tmp_vec[i]);
        result += (double)helper * (double)helper;
      }
      return (double)sqrt (result);
    }

    // gaussian elimination with partial pivoting
    T
    *backsub (T **A, T *b, int *pivot)
    {
      T*  solution  = new T[this->width];
      T*  ret       = new T[this->width];
      int n         = this->width;
      for (int i = n - 1; i >= 0; --i)
      {
        solution[pivot[i]] = b[pivot[i]];
        for (int j = i + 1; j < n; ++j)
        {
          solution[pivot[i]] = solution[pivot[i]] - A[pivot[i]][j] * solution[pivot[j]];
        }
        solution[pivot[i]] /= A[pivot[i]][i];
      }
      for (int i = 0; i < n; ++i)
      {
        ret[i] = solution[pivot[i]];
      }

      delete[] solution;
      return ret;
    }
    
    T
    *gaussian ()
    {
      T** A = clone_matrix (this->matrix, this->width);
      T*  b = clone_vector (this->vector, this->width);
      T *ret = nullptr;

      int m  = this->width - 1;
      int n  = this->width;

      int *pivot = new int[width];

      for (int i = 0; i < this->width; ++i)
      {
        pivot[i] = i;
      }

      for (int i = 0; i < m; ++i)
      {
        T magnitude = 0;
        int index   = -1;
        for (int j = i; j <= m; ++j)
        {
          if (fabs (A[pivot[j]][i]) > magnitude ) {
            magnitude = fabs (A[pivot[j]][i]);
            index = j;
          }
        }

        if (index != -1) {
          swap (pivot[i], pivot[index]);
        }

        for (int j = i + 1; j < n; ++j)
        {
          // calculate the ratio
          T ratio = A[pivot[j]][i] / A[pivot[i]][i];
          for (int k = i; k < n; ++k)
          {
            // modify matrix entry
            A[pivot[j]][k] = A[pivot[j]][k] - ratio * A[pivot[i]][k];
          }
          // modify result vector
          b[pivot[j]] = b[pivot[j]] - ratio * b[pivot[i]];
        }
      }

      ret = backsub (A, b, pivot);
      delete[] pivot;
      delete_matrix (A, this->width);
      delete_vector (b);

      return ret;
    }

    T *gaussian_improved ()
    {
      T** A = clone_matrix (this->matrix, this->width);
      T*  b = clone_vector (this->vector, this->width);
      T  *ret = nullptr;

      int m  = this->width - 1;
      int n  = this->width;

      int *pivot = new int[width];

      for (int i = 0; i < this->width; ++i)
      {
        pivot[i] = i;
      }

      for (int i = 0; i < m; ++i)
      {
        T magnitude = 0;
        int index   = -1;
        for (int j = i; j <= m; ++j)
        {
          if (fabs (A[pivot[j]][i]) > magnitude ) {
            magnitude = fabs (A[pivot[j]][i]);
            index = j;
          }
        }

        if (index != -1) {
          swap (pivot[i], pivot[index]);
        }

        for (int j = i + 1; j < n; ++j)
        {
          if (A[pivot[j]][i] == 0) {
            continue;
          }
          // calculate the ratio
          T ratio = A[pivot[j]][i] / A[pivot[i]][i];
          for (int k = i; k < n; ++k)
          {
            // modify matrix entry
            A[pivot[j]][k] = A[pivot[j]][k] - ratio * A[pivot[i]][k];
          }
          // modify result vector
          b[pivot[j]] = b[pivot[j]] - ratio * b[pivot[i]];
        }
      }

      ret = backsub (A, b, pivot);
      delete[] pivot;
      delete_matrix (A, this->width);
      delete_vector (b);

      return ret;
    }
    
    T
    *gauss_seidel_approx (double eps)
    {
      T **A = this->matrix;
      T  *b = this->vector;

      T* ret_vec = new T[this->width];
      T* tmp_vec = new T[this->width];
      T* pre_vec;

      double result;

      for (int i = 0; i < this->width; ++i)
      {
        tmp_vec[i] = 0;
        ret_vec[i] = 0;
      }

      do
      {
        pre_vec = clone_vector (ret_vec, this->width);
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec[i] = (b[i] / A[i][i]);
          for (int j = 0; j < this->width; ++j)
          {
            if (i == j) {
              continue;
            }
            ret_vec[i] = ret_vec[i] - ((A[i][j] / A[i][i]) * tmp_vec[j]);
            tmp_vec[i] = ret_vec[i];
          }
        }
        result = vector_norm (ret_vec, pre_vec, this->width);
        delete[] pre_vec;
      } while (result > eps);

      delete[] tmp_vec;
      return ret_vec;
    }

    T
    *jacobi_approx (double eps)
    {
      T **A = this->matrix;
      T  *b = this->vector;

      T  *ret_vec = new T[this->width];
      T  *tmp_vec;

      for (int i = 0; i < this->width; ++i)
      {
        ret_vec[i] = 0;
      }

      double result = 0.0;

      do {
        tmp_vec = clone_vector (ret_vec, this->width);
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec[i] = b[i];
          for (int j = 0; j < this->width; ++j)
          {
            if (i != j) {
              ret_vec[i] -= tmp_vec[j] * A[i][j];
            }            
          }
          ret_vec[i] /= A[i][i];
        }

        result = vector_norm (ret_vec, tmp_vec, this->width);
        delete[] tmp_vec;
      } while (result > eps);

      return ret_vec;
    }

    T
    *jacobi_iterative (int iterations)
    {
      T **A = this->matrix;
      T  *b = this->vector;

      T  *ret_vec = new T[this->width];
      T  *tmp_vec;

      for (int i = 0; i < this->width; ++i)
      {
        ret_vec[i] = 0;
      }

      int iterator = iterations;

      do {
        tmp_vec = clone_vector (ret_vec, this->width);
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec[i] = b[i];
          for (int j = 0; j < this->width; ++j)
          {
            if (i != j) {
              ret_vec[i] -= tmp_vec[j] * A[i][j];
            }            
          }
          ret_vec[i] /= A[i][i];
        }

        iterator--;
        delete[] tmp_vec;
      } while (iterator > 0);

      return ret_vec;
    }

    T
    *gauss_seidel_iterative (int iterations)
    {
      T **A = this->matrix;
      T  *b = this->vector;

      T  *ret_vec = new T[this->width];
      T  *tmp_vec;

      for (int i = 0; i < this->width; ++i)
      {
        ret_vec[i] = 0;
      }

      int iterator = iterations;

      do {
        tmp_vec = clone_vector (ret_vec, this->width);
        for (int i = 0; i < this->width; ++i)
        {
          ret_vec[i] = b[i];
          for (int j = 0; j < i; ++j)
          {
            ret_vec[i] = ret_vec[i] - (A[i][j] * tmp_vec[j]);
          }
          for (int j = i+1; j < this->width; ++j)
          {
            ret_vec[i] = ret_vec[i] - (A[i][j] * tmp_vec[j]);
          }
          ret_vec[i] = ret_vec[i] / A[i][i];
        }
        delete[] tmp_vec;
        iterator--;
      } while (iterator > 0);

      return ret_vec;
    }

    T
    count_abs_error (T* exemplary, T* after_test, int width)
    {
      T error_counter = 0;
      T val = 0;
      T def = 0;
      for (int i = 0; i < width; ++i)
      {
        def = exemplary[i] - after_test[i];
        val = abs (def);
        error_counter = error_counter + val;
      }
      error_counter = error_counter / width;
      return error_counter;
    }

    T
    count_abs_error (std::vector<T> exemplary, T* after_test, int width)
    {
      T error_counter = 0;
      T val = 0;
      T def = 0;
      for (int i = 0; i < width; ++i)
      {
        def = exemplary[i] - after_test[i];
        val = abs (def);
        error_counter = error_counter + val;
      }
      error_counter = error_counter / width;
      return error_counter;
    }

    T
    count_rel_error (std::vector<T> exemplary, T* after_test, int width)
    {
      T error_counter = 0;
      T val = 0;
      T def = 0;
      for (int i = 0; i < width; ++i)
      {
        def = exemplary[i] - after_test[i];
        val = abs (def);
        error_counter = error_counter + (val / abs (exemplary[i]));
      }
      error_counter = error_counter / width;
      return error_counter;
    }
};
#endif // PROTOCOLS_MATRIX_HH
