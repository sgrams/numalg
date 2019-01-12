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
#include <eigen3/Eigen/Sparse>
#include "util.hh"
#include "protocol.hh"
#include "sparsematrix.hh"
#include "probability.hh"
#include "generator.hh"


template <class T>
class SparseGenerator {
  private:
    int       agents_count;
    int       cases_count;
    Protocol* protocols_vector;

    Eigen::SparseMatrix<T> *matrix;
    Eigen::SparseVector<T> *vector;

  public:
    // constructors and destructors
    SparseGenerator (int agents_count)
    {
      this->agents_count = agents_count;
      this->cases_count = (agents_count + 1) * (agents_count + 2) / 2; // set cases count to the all generated cases qty
      this->protocols_vector = new Protocol[cases_count];

      this->vector = new Eigen::SparseVector<T> (this->cases_count);
      this->matrix = new Eigen::SparseMatrix<T> (this->cases_count, this->cases_count);
      this->generate_protocols_vector ();
      this->generate_probability_matrix ();
    }
    ~SparseGenerator ()
    {
      delete[] protocols_vector;
      if (matrix) {
        delete matrix;
      }
      if (vector) {
        delete vector;
      }
    }

    int
    get_agents_count ()
    {
      return this->agents_count;
    }

    int
    get_cases_count ()
    {
      return this->cases_count;
    }

    void
    set_agents_count (int agents_count)
    {
      this->agents_count = agents_count;
    }

    void
    set_cases_count (int cases_count)
    {
      this->cases_count = cases_count;
    }

    Eigen::SparseMatrix<T> *
    get_matrix ()
    {
      return this->matrix;
    }

    Eigen::SparseVector<T> *
    get_matrix_vector ()
    {
      return this->vector;
    }

    void
    set_matrix (Eigen::SparseMatrix<T> *matrix)
    {
      this->matrix = matrix;
    }

    void
    set_matrix_vector (Eigen::SparseVector<T> *vector)
    {
      this->vector = vector;
    }

    void
    generate_protocols_vector ()
    {
      for (int i = 0; i <= this->agents_count; i++)
      {
        for (int j = 0; j <= this->agents_count; j++)
        {
          if ((i + j) <= this->agents_count) {
            this->protocols_vector[i+j].set_yes_votes (i);
            this->protocols_vector[i+j].set_no_votes (j);
            this->protocols_vector[i+j].set_all_votes (this->agents_count);
            this->protocols_vector[i+j].set_undecided_votes (this->agents_count - i - j);
          }
        }
      }
    }
    void generate_probability_matrix ()
    {
      Probability *probability = new Probability (this->agents_count, this->cases_count);
      // create output (generated) vector
      this->vector->coeffRef (this->cases_count - 1) = 1;

      // create output (generated) matrix
      this->matrix->reserve ((int)std::sqrt (this->cases_count));
      for (int i = 0; i < this->cases_count; ++i)
      {
        for (int j = 0; j < this->cases_count; ++j)
        {
          T value = (T)probability->generate_value (this->protocols_vector, i, j);
          if (value == 0.0)
          {
            continue;
          }
          this->matrix->insert(i, j) = value;
        }
      }
      delete probability;
    }
};

#endif // APPROXIMATIONS_SPARSE_GENERATOR_HH