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
    T*  vector_X;
    T*  vector_B;

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

    int get_width () {
      return this->width;
    }
    T** get_matrix () {
      return this->matrix;
    };
    T* get_vector_X () {
      return this->vector_X;
    };
    T* get_vector_B () {
      return this->vector_B;
    };

    void set_vector_X (T* vector) {
      this->vector_X = vector;
    }
    void set_vector_B (T* vector) {
      this->vector_B = vector;
    }
    void set_matrix (T** matrix) {
      this->matrix = matrix;
    }

    // prints matrix
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

    T* gaussian_no_pivoting() {
      return this->vector_X;
    }
};
#endif // _GAUSS_GAUSS_H