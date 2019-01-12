/*
 *  This file is part of 04-approximations task.
 * 
 *  src/sparsegenerator.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef APPROXIMATIONS_SPARSE_GENERATOR_HH
#define APPROXIMATIONS_SPARSE_GENERATOR_HH
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "probability.hh"

template <class T>
class SparseGenerator : public Generator {
  private:
    int       agents_count;
    int       cases_count;
    Protocol* protocols_vector;

    Eigen::SparseMatrix<T> matrix;
    Eigen::VectorXd<T>     vector;

    // other procedures
    void
    generate_probability_matrix ();
    void
    generate_protocols_vector ();

  public:
    // constructors and destructors
    SparseGenerator (int agents_count);
   ~SparseGenerator ();

    Eigen::SparseMatrix<T>
    get_matrix ();
    Eigen::VectorXd<T>
    get_matrix_vector ();
    
    void
    set_matrix (Eigen::SparseMatrix<T> matrix);
    void
    set_matrix_vector (Eigen::VectorXd<T> vector);
};

#endif // APPROXIMATIONS_SPARSE_GENERATOR_HH