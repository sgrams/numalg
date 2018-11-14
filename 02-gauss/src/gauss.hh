#ifndef _GAUSS_GAUSS_H
#define _GAUSS_GAUSS_H
using namespace std;
#include <iostream>
#include <ctime>
#include <random>

#define RANDOMIZE_MIN_NUM -65536
#define RANDOMIZE_MAX_NUM  65535

template <typename T>
class MyMatrix {
  private:
    T** matrix;
    T*  results;
    int width;
  public:
    MyMatrix (int width) {
      this->width   = width;
      this->matrix  = new T*[width];
      this->results = new T[width];

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
      delete[] this->results;
    }
    int get_width () {
      return this->width;
    }
    T* get_results () {
      return this->results;
    };
    T** get_matrix () {
      return this->matrix;
    };
    // prints matrix
    void print () {
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
    // fills the matrix with random data
    void fill () {
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
    // basic backsub (without pivoting)
<<<<<<< Updated upstream
    T* backsub () {
      T  n        = this->width;
      T *solution = new T[this->width];
      
=======
    T* backsub (T** MATRIX) {
      T n = this->width;
      T *solution;
      solution = new T[this->width];
>>>>>>> Stashed changes
      for (int i = n - 1; i >= 0; --i) 
      {
       solution[i] = this->results[i];
        for (int j = i + 1; j < n; ++j) 
        {
          solution[i] = solution[i] - MATRIX[i][j] * solution[j];
        }
        solution[i] /= MATRIX[i][i];
      }
      return solution;
    }

    T* gaussian_no_pivoting() {
      T** partial;
      partial = new T*[this->width]; // to row reduce to upper triangular
      for (int i = 0; i < this->width; i++)
      {
        partial[i] = new T[this->width];
      }
      partial = this->matrix;
      // code here
      T nMinus1 = this->width - 1;
      T n = this->width;
      for (int i = 0; i < nMinus1; ++i) {
        for (int j = i + 1; j < n; ++j) {
          // calculate the ratio
          T ratio = partial[j][i] / partial[i][i];
          for (int k = i; k < n; ++k) {
            // modify matrix entry
            partial[j][k] = partial[j][k] - ratio * partial[i][k];
          }
            
          // modify result vector
          this->results[j] = this->results[j] - ratio * this->results[i];
          T rjAfter = this->results[j];
        }
      }
      return backsub(partial);
    }
};

#endif // _GAUSS_GAUSS_H