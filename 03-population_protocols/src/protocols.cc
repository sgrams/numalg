/*
 * This file is part of 03-population_protocol task.
 *
 * src/protocols.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 */
#include "protocols.hh"

class MonteCarlo {
  private:
    int iterations;
  public:
    MonteCarlo (int iterations);
   ~MonteCarlo ();


}

void
MonteCarlo::MonteCarlo (int iterations)
{
  this->iterations = iterations;
}


