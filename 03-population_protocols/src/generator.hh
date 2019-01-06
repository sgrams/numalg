/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/generator.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef PROTOCOLS_GENERATOR_HH
#define PROTOCOLS_GENERATOR_HH
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "probability.hh"

class
Generator {
  private:
    int       agents_count;
    int       cases_count;
    double  **protocols_equations;
    Protocol *protocols_vector;

    double **matrix;
    double  *matrix_vector;
  public:
    void   generate_probability_matrix ();
    void   generate_protocols_vector ();
};

#endif // PROTOCOLS_GENERATOR_HH