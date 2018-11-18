#ifndef _GAUSS_GAUSS_H
#define _GAUSS_GAUSS_H
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <gmp.h>

#define RANDOMIZE_MIN_NUM -65536
#define RANDOMIZE_MAX_NUM  65535

using namespace std;

typedef struct TC {
  mpq_t number;
  int   base = 10;
} TC_t;

template <typename T>
class MyMatrix {
  private:
    T **matrix;
    T  *vector_X;
    T  *vector_B;

    int width;
  public:
    MyMatrix (int width) {
      this->width    = width;
      this->matrix   = new T*[width];
      this->vector_X = new T[width];
      this->vector_B = new T[width];

      // create a square matrix of specified width
      for (int i = 0; i < width; i++)
      {
        matrix[i] = new T[width];
      }
    }
    ~MyMatrix () {
      for (int i = 0; i < this->width; i++)
      {
        delete[] this->matrix[i];
      }
      delete[] this->matrix;
      delete[] this->vector_X;
      delete[] this->vector_B;
    }

    // getters
    int get_width () {
      return this->width;
    }
    T **get_matrix () {
      return this->matrix;
    };
    T  *get_vector_X () {
      return this->vector_X;
    };
    T  *get_vector_B () {
      return this->vector_B;
    };

    // setters
    void set_vector_X (T *vector) {
      this->vector_X = vector;
    }
    void set_vector_B (T *vector) {
      this->vector_B = vector;
    }
    void set_matrix (T **matrix) {
      this->matrix = matrix;
    }

    // i/o streams operations
    void print_matrix () {
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

    void print_vector (T *vector, int width) {
      for (int i = 0; i < width; ++i)
      {
        cout << vector[i] << endl;
      }
    }

    // data fillers
    // fills matrix A with randomized data
    void fill_matrix () {
      T num;
      random_device rd;
      mt19937 eng(rd());
      uniform_int_distribution<> distr (RANDOMIZE_MIN_NUM, RANDOMIZE_MAX_NUM);

      for (int i = 0; i < width; ++i)
      {
        for (int j = 0; j < width; ++j)
        {
          num = distr (eng);
          num /= RANDOMIZE_MAX_NUM;
          this->matrix[i][j] = num;
        }
      }
    }
    // fills vector X with randomized data
    void fill_vector_X () {
      T num;
      random_device rd;
      mt19937 eng(rd());
      uniform_int_distribution<> distr (RANDOMIZE_MIN_NUM, RANDOMIZE_MAX_NUM);

      for (int i = 0; i < width; ++i)
      {
        num = distr (eng);
        num /= RANDOMIZE_MAX_NUM;
        this->vector_X[i] = num;
      }
    }
    // fills vector B by solving B=A*X
    void fill_vector_B () {
      for (int i = 0; i < width; ++i)
      {
        this->vector_B[i] = 0;
        for (int j = 0; j < width; ++j)
        {
          this->vector_B[i] += this->matrix[i][j] * this->vector_X[j];
        }
      }
    }

    // cloning methods for gaussian elimination methods
    T **clone_matrix (T **matrix, int width) {
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

    T *clone_vector (T *vector, int width) {
      T *b = new T[width];
      for (int i = 0; i < width; ++i)
      {
        b[i] = vector[i];
      }

      return b;
    }

    // delete methods for gaussian elimination methods
    void delete_matrix (T **matrix, int width) {
      for (int i = 0; i < width; ++i) {
        delete[] matrix[i];
      }
      delete[] matrix;
      return;
    }

    void delete_vector (T *vector) {
      delete[] vector;
      return;
    }
    
    T abs_generic (T x) {
      return x < 0 ? -x : x;
    }

    // gaussian elimination methods
    T *backsub_no_pivoting (T **A, T *b) {
      T* solution = new T[this->width];
      T n = this->width;

      for (int i = n - 1; i >= 0; --i)
      {
        solution[i] = b[i];
        for (int j = i + 1; j < n; ++j)
        {
          solution[i] = solution[i] - A[i][j] * solution[j];
        }
        solution[i] /= A[i][i];
      }

      return solution;
    }

    T *backsub_partial_pivoting (T **A, T *b, int *pivot) {
      T* solution  = new T[this->width];
      T* ret       = new T[this->width];
      T  n         = this->width;

      for (int i = n - 1; i >= 0; --i)
      {
        solution[pivot[i]] = b[pivot[i]];
        for (int j = i + 1; j < n; ++j)
        {
            solution[pivot[i]] = solution[pivot[i]] - A[pivot[i]][j] * solution[pivot[j]];
        }
        solution[pivot[i]] /= A[pivot[i]][i];
      }

      // translate the pivots back
      for (int i = 0; i < n; ++i)
      {
        ret[i] = solution[pivot[i]];
      }

      delete[] solution;
      return ret;
    }

    T *gaussian_no_pivoting () {
      // create copy of matrix and vector b
      T **A  = clone_matrix (this->matrix, this->width);
      T  *b  = clone_vector (this->vector_B, this->width);
      T   m  = this->width - 1;
      T   n  = this->width;
      T *ret = nullptr;

      for (int i = 0; i < m; ++i)
      {
        for (int j = i + 1; j < n; ++j)
        {
          T ratio = A[j][i] / A[i][i];
          for (int k = i; k < n; ++k)
          {
            A[j][k] = A[j][k] - ratio * A[i][k];
          }
          b[j] = b[j] - ratio * b[i];
        }
      }
    
    ret = backsub_no_pivoting (A, b);

    delete_matrix (A, this->width);
    delete_vector (b);

    return ret;
  }

  T *gaussian_partial_pivoting () {
    T **A  = clone_matrix (this->matrix, this->width);
    T  *b  = clone_vector (this->vector_B, this->width);
    T   m  = this->width - 1;
    T   n  = this->width;
    T *ret = nullptr;

    int pivot[this->width];

    for (int i = 0; i < this->width; ++i)
    {
      pivot[i] = i;
    }

    for (int i = 0; i < m; ++i)
    {
      // do the pivot first
      T magnitude = 0;
      int index   = -1;
      for (int j = i; j <= m; ++j)
      {
        if (abs_generic (A[pivot[j]][i]) > magnitude ) {
          magnitude = abs_generic (A[pivot[j]][i]);
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

    // call overloaded backsub for partial pivoting
    ret = backsub_partial_pivoting (A, b, pivot);
    delete_matrix (A, this->width);
    delete_vector (b);

    return ret;
  }

};
#endif // _GAUSS_GAUSS_H