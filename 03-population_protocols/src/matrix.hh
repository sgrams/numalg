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
      T **A  = clone_matrix (this->matrix, this->width);
      T  *b  = clone_vector (this->vector, this->width);
      T *ret = nullptr;

      int m  = this->width - 1;
      int n  = this->width;

      int pivot[this->width];

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
          if (abs (A[pivot[j]][i]) > magnitude ) {
            magnitude = abs (A[pivot[j]][i]);
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

      ret = backsub_partial_pivoting (A, b, pivot);
      delete_matrix (A, this->width);
      delete_vector (b);

      return ret;
    }

    T
    *jacobi_iterative (int iterations)
    {
      T **A  = clone_matrix (this->matrix, this->width);
      T  *b  = clone_vector (this->vector, this->width);
      T *x_1 = new T[width];
      T *x_2 = new T[width];

      int n  = this->width;
      int counter = 0;
      int i, j;

      double result, sum, helper;

      // initialize x
      for (i = 0; i < n; ++i)
      {
        x_1[i] = 0;
      }

      do
      {
        counter++;
        x_2 = x_1;

        for (i = 0; i < n; ++i)
        {
          sum = 0;
          for (j = 1; j < n; ++j)
          {
            if (i != j)
              sum += A[i][j] * x_1[j];
          }
          x_1[i] = (-sum + b[i]) / A[i][i];
          if (x_1[i] == -0.0)
            x_1[i] = 0.0;
        }

        helper = 0;
        result = 0;

        for (i = 0; i < n; ++i)
        {
          helper = fabs(x_1[i] - x_2[i]);
          result += helper * helper;
        }

        result = sqrt(result);
      } while (counter < iterations);
      
      return x_1;
    }


/*
    T
    *jacobi_approx (double eps)
    {
      T **A  = clone_matrix (this->matrix, this->width);
      T  *b  = clone_vector (this->vector_B, this->width);
      T *x_1 = new T*[width];
      T *x_2 = new T*[width];

      int n  = this->width;
      int counter = 0;
      int i, j, k;

      double result, sum, helper;

      // initialize x
      for (i = 0; i < n; ++i)
      {
        x_1[i] = 0;
      }





      
      

    }
    */
    
    T *GSeidel(double eps) 
    {
      T dzielnik, norma1, norma2;
      bool koniec;
      T **A  = clone_matrix (this->matrix, this->width);
      T  *B  = clone_vector (this->vector_B, this->width);
      T *B2 = new T[this->width];
      T *x = new T[this->width];
      T *x2 = new T[this->width];
      T **U = new T*[this->width];
      T **L = new T*[this->width];
      T **D = new T*[this->width];
      T **I = new T*[this->width];

      for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->width; j++)
          {
            L[i][j] = 0;
            U[i][j] = 0;
            D[i][j] = 0;
            I[i][j] = 0;
          }
        }

      for (int i = 0; i < this->width; i++)
      {
        for (int j = 0; j < this->width; j++)
        {
          // utworzenie macierzy dolnotrojkatnej
          if (i > j)  
            L[i][j] = A[i][j];
            // utworzenie macierzy gornotrojkatnej
          else if (i < j)
            U[i][j] = A[i][j];
          else
          {
            // utworzenie macierzy z przekatnej macierzy glownej
            D[i][i] = A[i][i];
            // jedynki na przekatnej
            I[i][i] = 1;
            }
          }
      }
        // wyznaczenie p = min{||-(L+D)^-1 * N||:||-(L+D)^-1 * N||}
        
      // obliczenie D + L (wynik w L)
      for (int i = 0; i < this->width; i++)
        L[i][i] = D[i][i];
      // obliczenie (D + L)^-1 (wynik w I)
      for (int i = 0; i < this->width; i++)
      {
        dzielnik = L[i][i];
        for (int j = 0; j < this->width; j++)
        {
          L[i][j] /= (double)dzielnik;
          I[i][j] /= (double)dzielnik;
        }
        for (int k = 0; k < this->width; k++)
        {
          if (k == i) continue;
            dzielnik = L[k][i];
          for (int j = 0; j < this->width; j++)
          {
            L[k][j] -= (double)(L[i][j] * dzielnik);
            I[k][j] -= (double)(I[i][j] * dzielnik);
          }
        }
      }
        // obliczenie (L + D)^-1 * N (wynik w L)
      for (int i = 0; i < this->width; i++)
      {
        for (int j = 0; j < this->width; j++)
        {
          L[i][j] = 0;
          for (int k = 0; k < this->width; k++)
            L[i][j] += (double)(I[i][k] * U[k][j]);
        }
      }
        
      // obliczenie -(L+D)^-1 * N
      for (int i = 0; i < this->width; i++)
        for (int j = 0; j < this->width; j++)
          L[i][j] *= (double)(-1);
      // norma "jeden"
      norma1 = 0;
      for (int i = 0; i < this->width; i++)
      {
        dzielnik = 0;
        for (int j = 0; j < this->width; j++)
          dzielnik += fabs(L[j][i]);
        if (dzielnik > norma1) norma1 = dzielnik;
      }
      // norma "nieskonczonosc"
      norma2 = 0;
      for (int i = 0; i < this->width; i++)
      {
        dzielnik = 0;
        for (int j = 0; j < this->width; j++)
          dzielnik += fabs(L[i][j]);
        if (dzielnik > norma2) norma2 = dzielnik;
      }
        
      // p = min(norma1, norma2)
      if (norma1 > norma2) norma1 = norma2;
        
      // ciag nie jest zbiezny do rozwiazania ukladu rownan
      if (norma1 >= 1)
        norma1 = 0.5;
        
      // inicjalizacja wektora wynikow
      for (int i = 0; i < this->width; i++)
        x[i] = 0;
        
      koniec = true;
      do
      {
        // przepisanie x - aktualnych wynikow do x2 - wynikow z poprzedniej iteracji
        for (int i = 0; i < this->width; i++)
          x2[i] = x[i];        
          
          // wykonanie kolejnej iteracji
          for (int i = 0; i < this->width; i++)
          {
            B2[i] = B[i];       
            for (int j = 0; j < i; j++)
              B2[i] -= (A[i][j] * x[j]);    
            for (int j = i + 1; j < this->width; j++)
              B2[i] -= A[i][j] * x2[j];  
              x[i] = (double)(B2[i] / A[i][i]);
          }
            
            // sprawdzenie warunku zakonczenia: ||x(k)-x(k-1)|| <= epsilon
            for (int i = 0; i < this->width; i++)
            {
                if (fabs(x[i] - x2[i]) > eps) { koniec = true; break; }
                else koniec = false;
            }
      }while (koniec);
        
      // wyswietlenie wyniku
      //std::cout << "Wynik GSeidel:\n";
      for (int i = 0; i < this->width; i++) 
      {
        if (x[i] == -0.0) 
        {
          x[i] = 0.0;
        }
      }
      return x;  
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
    count_rel_error (T* exemplary, T* after_test, int width)
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
