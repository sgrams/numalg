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
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include "util.hh"

enum state_t {
  NO,       // 0: keeps the boolean logic correct
  YES,      // 1
  UNDECIDED // 2
};

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
    bool    is_ready;
  public:
    Agent (state_t state);
    void    change_state (Agent agent);
    void    set_state (state_t state);
    state_t get_state ();
    bool    ready ();
    void    make_ready();
};

class
MonteCarlo {
  private:
    int iterations;
    int all_agents;

  public:
    MonteCarlo (int iterations, int all_agents);
   ~MonteCarlo ();
    double  run_simulation (int yes_votes, int no_votes);
    state_t run_simulation_helper (std::vector<Agent> simulation_vector);
};
#endif