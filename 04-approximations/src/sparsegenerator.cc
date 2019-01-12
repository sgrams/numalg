/*
 *  This file is part of 04-approximations task.
 * 
 *  src/sparsegenerator.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "sparsegenerator.hh"
SparseGenerator::SparseGenerator (int agents_count)
{
  this->agents_count = agents_count;
  this->cases_count = (agents_count + 1) * (agents_count + 2) / 2; // set cases count to the all generated cases qty
  this->protocols_vector = new Protocol[cases_count];
  this->generate_protocols_vector ();
  this->generate_probability_matrix ();
}