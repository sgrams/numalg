/*
 * This file is part of 03-population_protocol task.
 *
 * src/protocols.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 */
#include "protocols.hh"
// main construcotr for Protocols class
Protocols::Protocols (int yes_votes, int no_votes, int all_votes) {
  this->all_votes       = all_votes;
  this->yes_votes       = yes_votes;
  this->no_votes        = no_votes;
  this->undecided_votes = all_votes - yes_votes - no_votes;
}

// getters and setters for Protocols class
double
Protocols::get_yes_votes () {
  return this->yes_votes;
}
double
Protocols::get_no_votes () {
  return this->no_votes;
}
double
Protocols::get_undecided_votes () {
  return this->undecided_votes;
}
double
Protocols::get_all_votes () {
  return this->all_votes;
}

void
Protocols::set_yes_votes (double yes_votes) {
  this->yes_votes = yes_votes;
}
void
Protocols::set_no_votes (double no_votes) {
  this->no_votes = no_votes;
}
void
Protocols::set_undecided_votes (double undecided_votes) {
  this->undecided_votes = undecided_votes;
}
void
Protocols::set_all_votes (double all_votes) {
  this->all_votes = all_votes;
}

MonteCarlo::MonteCarlo (int iterations)
{
  this->iterations = iterations;
}


