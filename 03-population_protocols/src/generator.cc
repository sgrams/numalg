/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/generator.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "generator.hh"

void
Generator::generate_protocols_vector () {
  int iter = 0;
  this->protocols_vector = new Protocol[this->agents_count];
  for (int i = 0; i < this->agents_count; ++i)
  {
    for (int j = 0; j < this->agents_count; ++j)
    {
      if ((i + j) <= this->agents_count) {
        this->protocols_vector[iter].set_yes_votes (this->agents_count);
        this->protocols_vector[iter].set_no_votes (i);
        this->protocols_vector[iter].set_undecided_votes (j);
        iter++;
      }
    }
  }
  this->cases_count = iter - 1; // set cases count to the all generated cases qty
}

void
Generator::generate_probability_matrix () {
  Probability *probability = new Probability (this->agents_count, this->cases_count);
  // create output (generated) vector
  this->matrix_vector = new double[this->cases_count];
  for (int i = 0; i < this->cases_count - 1; ++i)
  {
    this->matrix_vector[i] = 0;
  }
  this->matrix_vector[this->cases_count - 1] = 1;

  // create output (generated) matrix
  this->matrix = new double*[this->cases_count];
  for (int i = 0; i < this->cases_count; ++i)
  {
    this->matrix[i] = new double [this->cases_count];
    for (int j = 0; j < this->cases_count; ++j)
    {
      this->matrix[i][j] = probability->generate_value (this->protocols_vector, i, j);
    }
  }
}