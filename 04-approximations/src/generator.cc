/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/generator.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "generator.hh"

Generator::Generator (int agents_count)
{
  this->agents_count = agents_count;
  this->cases_count = (agents_count + 1) * (agents_count + 2) / 2; // set cases count to the all generated cases qty
  this->protocols_vector = new Protocol[cases_count];
  this->generate_protocols_vector ();
  this->generate_probability_matrix ();
}
Generator::~Generator ()
{
  delete[] protocols_vector;

  if (this->matrix) {
    for (int i = 0; i < this->cases_count; ++i)
    {
      delete[] this->matrix[i];
    }
    delete[] this->matrix;
  }
  
  if (matrix_vector) {
    delete[] matrix_vector;
  }
}

int
Generator::get_agents_count ()
{
  return this->agents_count;
}

int
Generator::get_cases_count ()
{
  return this->cases_count;
}

Protocol *
Generator::get_protocols_vector ()
{
  return this->protocols_vector;
}

double **
Generator::get_matrix ()
{
  return this->matrix;
}

double *
Generator::get_matrix_vector ()
{
  return this->matrix_vector;
}

void
Generator::set_agents_count (int agents_count)
{
  this->agents_count = agents_count;
}

void
Generator::set_cases_count (int cases_count)
{
  this->cases_count = cases_count;
}

void
Generator::set_protocols_vector (Protocol* protocols_vector)
{
  this->protocols_vector = protocols_vector;
}

void
Generator::set_matrix (double **matrix)
{
  this->matrix = matrix;
}

void
Generator::set_matrix_vector (double *matrix_vector)
{
  this->matrix_vector = matrix_vector;
}


void
Generator::generate_protocols_vector ()
{
  int iter = 0;
  for (int i = 0; i <= this->agents_count; i++)
  {
    for (int j = 0; j <= this->agents_count; j++)
    {
      if ((i + j) <= this->agents_count) {
        this->protocols_vector[iter].set_yes_votes (i);
        this->protocols_vector[iter].set_no_votes (j);
        this->protocols_vector[iter].set_all_votes (this->agents_count);
        this->protocols_vector[iter].set_undecided_votes (this->agents_count - i - j);
        iter++;
      }
    }
  }
}

void
Generator::generate_probability_matrix ()
{
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
    this->matrix[i] = new double[this->cases_count];
    for (int j = 0; j < this->cases_count; ++j)
    {
      this->matrix[i][j] = probability->generate_value (this->protocols_vector, i, j);
      cout << this->matrix[i][j] << " ";
    }
    cout << endl;
  }
  delete probability;
}