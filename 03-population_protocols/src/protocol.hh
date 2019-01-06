/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/protocol.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef PROTOCOLS_PROTOCOL_HH
#define PROTOCOLS_PROTOCOL_HH
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "util.hh"

typedef enum state {
  NO,       // 0: keeps the boolean logic correct
  YES,      // 1
  UNDECIDED // 2
} state_t;

class
Protocol {
  private:
    int yes_votes;
    int no_votes;
    int undecided_votes;
    int all_votes;
  public:
    Protocol ();
    Protocol (int yes_votes, int no_votes, int all_votes);
    // getters and setters
    int get_yes_votes ();
    int get_no_votes ();
    int get_undecided_votes ();
    int get_all_votes ();

    void set_yes_votes (int yes_votes);
    void set_no_votes (int no_votes);
    void set_undecided_votes (int undecided_votes);
    void set_all_votes (int all_votes);
};

class
Agent {
  private:
    state_t state;
  public:
    Agent (state_t state);
    void change_state (Agent &agent);
};

class
MonteCarlo {
  private:
    int iterations;
    int all_agents;
  public:
    MonteCarlo (int iterations);
   ~MonteCarlo ();
};
#endif