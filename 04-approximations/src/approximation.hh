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
    Approximation (int *arguments, T *values, int polynomial, int size)
    {
      this->arguments  = arguments;
      this->values     = values;
      this->polynomial = polynomial + 1;
      this->size = size;
    }


/*
    void printResult(T *results)
    {
      cout << "f(x) = " << endl;

      for (int i = 0; i < results.size (); ++i)
        {
          if (i != 0) {
          cout << " + " << endl;
        }
        cout << "(" << results[i] << " * x^" << i << ")" << endl;
        }
      cout << endl;
    }

    */

    T *
    perform_operations ()
    {


      T **mat_A = new T*[size];
      T **mat_B = new T*[polynomial];


      // initialize matrices
      for (int i = 0; i < size; ++i)
      {
        mat_A[i] = new T[polynomial];
      }
      
      for (int i = 0; i < polynomial; ++i)
      {
        mat_B[i] = new T[size];
      }
  

        for (int i = 0; i < size; ++i)
        {
          cout << "test_1 " << i << endl;
          for (int j = 0; j < polynomial; ++j)
          {
            cout << "test_2" << i << endl;

           // mat_B[i][j] = std::pow (this->arguments[i], j);
           //mat_A[j][i] = mat_B[i][j];
          }
        }
                cout << "end" << endl;

      
/*
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
*/
      T *vec_A = new T[polynomial];
      for (int i = 0; i < polynomial; ++i)
      {
        // initialize vec_A
        vec_A[i] = 0;
        for (int j = 0; j < polynomial; ++j)
        {
          //vec_A[i] += mat_A[i][j] * this->values[j];
         // cout << vec_A[i] << endl;
        }
      }
      
     // MyMatrix<double> *matrix = new MyMatrix<double>(polynomial, mat_C, vec_A);
      
      //T *ret = new T[polynomial];
     // ret = matrix->gaussian ();

     /* matrix->delete_matrix (mat_A, polynomial);
      matrix->delete_matrix (mat_B, size);
      matrix->delete_matrix (mat_C, polynomial);
      delete[] vec_A;
      delete matrix; 
      */     


      return vec_A;
      
    }
};
#endif // APPROXIMATION_APPROXIMATION_H