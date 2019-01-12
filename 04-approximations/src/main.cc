/*
 * This file is part of 04-approximations task.
 *
 * src/main.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "generator.hh"
#include "probability.hh"

#define DEFAULT_MONTECARLO_ITERATIONS 10000 // 10k
#define DEFAULT_MIN_VALIDATION_ITERATIONS 10
#define DEFAULT_MAX_VALIDATION_ITERATIONS 10000 // 1mln
#define DEFAULT_VALIDATION_ITERATIONS_STEP 10
#define DEFAULT_JACOBI_ITERATIONS     1000 //  1k
#define DEFAULT_JACOBI_EPSILON        0.00000000000001 // 10^-14
#define DEFAULT_SEIDEL_ITERATIONS     1000 //  1k
#define DEFAULT_SEIDEL_EPSILON        0.00000000000001 // 10^-14
#define DEFUALT_MIN_ITERATIONS        1
#define DEFAULT_MAX_ITERATIONS        1000
#define DEFAULT_ITERATIONS_STEP       10
#define DEFAULT_MIN_AGENT_COUNT       3
#define DEFAULT_MAX_AGENTS_COUNT      20
#define DEFAULT_VALIDATION_AGENTS_COUNT 5

using namespace std;

int main (int argc, char *argv[])
{

  return EXIT_SUCCESS;
}