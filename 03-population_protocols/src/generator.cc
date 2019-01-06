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
generate_protocols_vector () {
  this->protocols_vector = new Protocol[this->agents_count];

  for (int i = 0, int iter = 0; i < this->agents_count; ++i)
  {
    for (int j = 0; j < this->agents_count; ++j)
    {
      if ((i + j) <= this->agents_count) {
        this->protocols_vector[iter++] = Protocol (this->agents_count, i, j);
      }
    }
  }
  this->cases_count = iter - 1; // set cases count to the all generated cases qty
}

void
generate_protocols_equations () {
  // create output (generated) vector
  this->matrix_vector = new double[this->cases_count];
  for (int i = 0; i < this->cases_count - 1; ++i)
  {
    this->matrix_vector[i] = 0;
  }
  this->matrix_vector[this->cases_count - 1] = 1;

  // create output (generated) matrix
  this->matrix = new double[this->cases_count];
  for (int i = 0; i < this->cases_count; ++i)
  {
    this->matrix[i] = new double [this->cases_count];
    for (int j = 0; j < this->cases_count; ++j)
    {
      this->matrix[i][j] = generate_protocol_values (i, j);
    }
  }
}

double
generate_protocol_values (int row, int col) {
  int yes_votes_in_row = this->protocols_vector[row].yes_votes;
  int no_votes_in_row  = this->protocols_vector[row].no_votes;
  int undecided_votes_in_row = this->protocols_vector[row].undecided_votes;

  int yes_votes_in_col = this->protocols_vector[col].yes_votes;
  int no_votes_in_col  = this->protocols_vector[col].no_votes;

  if ((yes_votes_in_row == this->agents_count || no_votes_in_row == this->agents_count)
      && row == col)
    {
      return 1.0;
  }

  if (yes_votes_in_row == 0 && no_votes_in_row == 0 && i == j) {
    return 1.0;
  }

  // some moar casez
  
  if (i == j) {
    return -1.0;
  }

  return 0.0;
}