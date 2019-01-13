/*
 * This file is part of 04-approximations task.
 *
 * src/main.cc
 * Stanisław Grams <sgrams@fmdx.pl>
 * Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "sparsematrix.hh"
#include "generator.hh"
#include "sparsegenerator.hh"
#include "probability.hh"
#include "approximation.hh"

#define DEFAULT_GS_EPSILON            0.0000000001 // 1e^-10
#define DEFAULT_SPARSE_GS_EPSILON     0.0000000001 // 1e^-10
#define DEFAULT_MIN_AGENTS_COUNT       3
#define DEFAULT_MAX_AGENTS_COUNT      60

using namespace std;
typedef enum {
  G,
  G_SPARSE,
  GS_1E10,
  GS_EIGEN,
  LU_EIGEN,
} types_t;

typedef struct {
  double **calculation_measurements;
  double **generator_measurements;
} measurement_t;

void
delete_measurements (measurement_t *measurements, int min_agents_count, int max_agents_count)
{
  for (int i = 0; i < max_agents_count - min_agents_count + 1; ++i)
  {
    delete[] measurements->calculation_measurements[i];
    delete[] measurements->generator_measurements[i];
  }
  delete[] measurements->calculation_measurements;
  delete[] measurements->generator_measurements;
  delete measurements;
}

measurement_t *
get_measurements (types_t type, int min_agents_count, int max_agents_count)
{
  Generator *g;
  MyMatrix<double> *m;

  SparseGenerator<double> *sg;
  MySparseMatrix<double> *sm;

  measurement_t *measurements = new measurement_t;
  measurements->calculation_measurements = new double*[max_agents_count - min_agents_count + 1];
  measurements->generator_measurements   = new double*[max_agents_count - min_agents_count + 1];
  
  for (int i = min_agents_count; i <= max_agents_count; ++i)
  {
    // reserve some memory
    measurements->generator_measurements[i-min_agents_count] = new double[2];
    measurements->calculation_measurements[i-min_agents_count] = new double[2];

    clock_t begin_generating_time = clock ();
    if (type == GS_EIGEN || type == LU_EIGEN) {
      sg = new SparseGenerator<double>(i);
    } else {
      g = new Generator (i);
    }
    clock_t end_generating_time = clock ();

    // save measurement to measurements structure
    measurements->generator_measurements[i-min_agents_count][0] = i;
    measurements->generator_measurements[i-min_agents_count][1] = (double)(end_generating_time - begin_generating_time) / CLOCKS_PER_SEC;
    // transfer generated structured to MyMatrix/MySparseMatrix object (by pointers -> in almost no time)
    if (type == GS_EIGEN || type == LU_EIGEN) {
      sm = new MySparseMatrix<double> (sg->get_cases_count (), sg->get_matrix (), sg->get_matrix_vector ());
    } else {
      m = new MyMatrix<double> (g->get_cases_count (), g->get_matrix (), g->get_matrix_vector ());
    }

    // begin calculations
    clock_t begin_calculation_time;
    clock_t end_calculation_time;
    double *ret_vec;
    switch (type)
    {
      case G:
        begin_calculation_time = clock ();
        ret_vec = m->gaussian ();
        end_calculation_time = clock ();
        break;
      case G_SPARSE:
        begin_calculation_time = clock ();
        ret_vec = m->gaussian_improved ();
        end_calculation_time = clock ();
        break;
      case GS_1E10:
        begin_calculation_time = clock ();
        ret_vec = m->gauss_seidel_approx (DEFAULT_GS_EPSILON);
        end_calculation_time = clock ();
        break;
      case GS_EIGEN:
        begin_calculation_time = clock ();
        sm->sparse_GS_approx (DEFAULT_SPARSE_GS_EPSILON);
        end_calculation_time = clock ();
        break;
      case LU_EIGEN:
        begin_calculation_time = clock ();
        sm->sparse_LU ();
        end_calculation_time = clock ();
        break;
    }
    measurements->calculation_measurements[i-min_agents_count][0] = i;
    measurements->calculation_measurements[i-min_agents_count][1] = (double)(end_calculation_time - begin_calculation_time) / CLOCKS_PER_SEC;
    if (type == GS_EIGEN || type == LU_EIGEN) {
      delete sg;
      delete sm;
    } else {
      delete[] ret_vec;
      delete g;
      delete m;
    }
  }
  return measurements;
}

void
perform_calculations ()
{
  measurement_t *gaussian = get_measurements (G, DEFAULT_MIN_AGENTS_COUNT, 5);
  for (int i = 0; i < 3; ++i)
  {
    cout << "generator results:\n";
    cout << gaussian->generator_measurements[i][0] << ": " << gaussian->generator_measurements[i][1] << endl;
  }
  for (int i = 0; i < 3; ++i)
  {
    cout << "calculation results:\n";
    cout << gaussian->calculation_measurements[i][0] << ": " << gaussian->calculation_measurements[i][1] << endl;
  }
  delete_measurements (gaussian, DEFAULT_MIN_AGENTS_COUNT, 5);
}

int main (int argc, char *argv[])
{
  // Approximation<double> ap = Approximation<double>(arguments, values, 5, 2);
  // double *ap_vec = ap.run ();
  perform_calculations ();
  return EXIT_SUCCESS;
}