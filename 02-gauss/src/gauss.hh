#ifndef _GAUSS_GAUSS_H
#define _GAUSS_GAUSS_H
using namespace std;
#include <iostream>
#include <ctime>
#include <random>
#include<algorithm>

#define RANDOMIZE_MIN_NUM -65536
#define RANDOMIZE_MAX_NUM  65535

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
    void print_vector_X () {
      for (int i = 0; i < width; ++i)
      {
        cout << this->vector_X[i] << endl;
      }
    }
    void print_vector_B () {
      for (int i = 0; i < width; ++i)
      {
        cout << this->vector_B[i] << endl;
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
    
    T absGeneric(T X) {
      if (X < 0) X *= -1;
      return X;
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

    T *backsub_partial_pivoting (T **A, T *b, int *piv) {
      T* solution = new T[this->width];
      T* solution2 = new T[this->width];
      T n = this->width;

      for (int i = n - 1; i >= 0; --i) {
        solution[piv[i]] = b[piv[i]];
        for (int j = i + 1; j < n; ++j) {
            solution[piv[i]] = solution[piv[i]] - A[piv[i]][j] * solution[piv[j]];
        }
        solution[piv[i]] /= A[piv[i]][i];
      }

      // translate the pivots back
      for (int i = 0; i < n; ++i)
      {
        solution2[i] = solution[piv[i]];
      }

      return solution2;
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
    T   m  = width - 1;
    T   n  = width;
    int piv[this->width];

    for (int i = 0; i < this->width; ++i) {
      piv[i] = i;
    }

    for (int i = 0; i < m; ++i) {
      // do the pivot first
      T magnitude = 0;
      int index = -1;
      for (int j = i; j <= m; ++j) {
        if (absGeneric(A[piv[j]][i]) > magnitude ) {
          magnitude = absGeneric(A[piv[j]][i]);
          index = j;
        }
      }

      if (index != -1) {
        swap(piv[i], piv[index]);
      }

      for (int j = i + 1; j < n; ++j) {
        // calculate the ratio
        T ratio = A[piv[j]][i] / A[piv[i]][i];

        for (int k = i; k < n; ++k) {
          // modify matrix entry
          A[piv[j]][k] = A[piv[j]][k] - ratio * A[piv[i]][k];
        }

        // modify result vector
        b[piv[j]] = b[piv[j]] - ratio * b[piv[i]];
      }
    }

    // call overloaded backsub for partial pivoting
    return backsub_partial_pivoting(A, b, piv);

  }

};
#endif // _GAUSS_GAUSS_H