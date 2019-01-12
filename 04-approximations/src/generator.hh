/*
 *  This file is part of 04-approximations task.
 * 
 *  src/approximations.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef APPROXIMATIONS_GENERATOR_HH
#define APPROXIMATIONS_GENERATOR_HH
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
    Protocol* protocols_vector;

    double **matrix;
    double  *matrix_vector;
  public:
    // constructors and destructors
    Generator (int agents_count);
   ~Generator ();
    // getters and setters
    int
    get_agents_count ();
    int
    get_cases_count ();
    Protocol*
    get_protocols_vector ();
    double **
    get_matrix ();
    double *
    get_matrix_vector ();

    void
    set_agents_count (int agents_count);
    void
    set_cases_count (int cases_count);
    void
    set_protocols_vector (Protocol* protocols_vector);
    void
    set_matrix (double **matrix);
    void
    set_matrix_vector (double *matrix_vector);

    // other procedures
    void
    generate_probability_matrix ();
    void
    generate_protocols_vector ();
};

#endif // APPROXIMATIONS_GENERATOR_HH