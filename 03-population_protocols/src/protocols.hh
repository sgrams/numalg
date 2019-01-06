/*
 * This file is part of 03-population_protocol task.
 *
 * src/protocols.hh
 * Stanisław Grams <sgrams@fmdx.pl>
 */
#ifndef PROTOCOLS_PROTOCOLS_HH
#define PROTOCOLS_PROTOCOLS_HH
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "util.hh"

typedef enum state {
  Y,
  N,
  U
} state_t;

class
Protocols {
  private:
    int yes_votes;
    int no_votes;
    int undecided_votes;
    int all_votes;
  public:
    Protocols (int yes_votes, int no_votes, int all_votes);
    // getters and setters
    double get_yes_votes ();
    double get_no_votes ();
    double get_undecided_votes ();
    double get_all_votes ();

    void set_yes_votes (double yes_votes);
    void set_no_votes (double no_votes);
    void set_undecided_votes (double undecided_votes);
    void set_all_votes (double all_votes);
};

class MonteCarlo {
  private:
    int iterations;
  public:
    MonteCarlo (int iterations);
   ~MonteCarlo ();
};
#endif