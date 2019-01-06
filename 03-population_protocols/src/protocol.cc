/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/protocol.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "protocol.hh"
/*
 * Protocol Class
 */
// main constructor for Protocol class
Protocol::Protocol ()
{
  this->all_votes       = 0;
  this->yes_votes       = 0;
  this->no_votes        = 0;
  this->undecided_votes = 0;
}

Protocol::Protocol (int yes_votes, int no_votes, int all_votes)
{
  this->all_votes       = all_votes;
  this->yes_votes       = yes_votes;
  this->no_votes        = no_votes;
  this->undecided_votes = all_votes - yes_votes - no_votes;
}

// getters and setters for Protocol class
int
Protocol::get_yes_votes ()
{
  return this->yes_votes;
}

int
Protocol::get_no_votes ()
{
  return this->no_votes;
}

int
Protocol::get_undecided_votes ()
{
  return this->undecided_votes;
}

int
Protocol::get_all_votes ()
{
  return this->all_votes;
}

void
Protocol::set_yes_votes (int yes_votes)
{
  this->yes_votes = yes_votes;
}

void
Protocol::set_no_votes (int no_votes)
{
  this->no_votes = no_votes;
}

void
Protocol::set_undecided_votes (int undecided_votes)
{
  this->undecided_votes = undecided_votes;
}

void
Protocol::set_all_votes (int all_votes)
{
  this->all_votes = all_votes;
}

/*
 * Agent Class
 */
Agent::Agent (state_t state)
{
  this->state = state;
}

void
Agent::change_state (Agent &agent)
{

}

/*
 * MonteCarlo Class
 */
MonteCarlo::MonteCarlo (int iterations)
{
  this->iterations = iterations;
}