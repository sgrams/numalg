/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/probability.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef PROTOCOLS_PROBABILITY_HH
#define PROTOCOLS_PROBABILITY_HH
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include "util.hh"
#include "protocol.hh"
#include "generator.hh"
#include "matrix.hh"

class
Probability
{
  private:
    int agents_count;
    int cases_count;
  public:
    Probability (int agents_count, int cases_count);

    double
    generate_value (std::vector<Protocol> protocols_vector, int row, int col);
    double
    get_agents_count ();
    void
    set_agents_count (int agents_count);
    double
    get_cases_count ();
    void
    set_cases_count (int agents_count);

    double
    case_undecided_agents (Protocol protocol);
    double
    case_one_undecided_agent (Protocol protocol, int condition);
    double
    case_mixed_agents (Protocol protocol);
};

#endif //PROTOCOLS_PROBABILITY_HH