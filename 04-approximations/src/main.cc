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

#define DEFAULT_G_POLYNOMIAL 3
#define DEFAULT_G_SPARSE_POLYNOMIAL 2
#define DEFAULT_GS_1E10_POLYNOMIAL 2
#define DEFAULT_GS_EIGEN_POLYNOMIAL 2
#define DEFAULT_LU_EIGEN_POLYNOMIAL 1

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
  int size;
} measurement_t;

typedef struct {
  double *vector;
  int size;
} polynomial_t;

void
delete_polynomial (polynomial_t *polynomial)
{
  delete[] polynomial->vector;
}

void
delete_measurement (measurement_t *measurements)
{
  for (int i = 0; i < 2; ++i)
  {
    delete[] measurements->calculation_measurements[i];
    delete[] measurements->generator_measurements[i];
  }
  delete[] measurements->calculation_measurements;
  delete[] measurements->generator_measurements;
  delete measurements;
}

measurement_t *
run_measurement (types_t type, int min_agents_count, int max_agents_count)
{
  Generator *g;
  MyMatrix<double> *m;

  SparseGenerator<double> *sg;
  MySparseMatrix<double> *sm;

  // reserve some memory
  measurement_t *measurements = new measurement_t;
  measurements->calculation_measurements = new double*[2];
  measurements->generator_measurements   = new double*[2];
  measurements->size = max_agents_count - min_agents_count + 1;
  for (int i = 0; i < 2; ++i)
  {
    measurements->generator_measurements[i] = new double[max_agents_count - min_agents_count + 1];
    measurements->calculation_measurements[i] = new double[max_agents_count - min_agents_count + 1];
  }

  for (int i = min_agents_count; i <= max_agents_count; ++i)
  {
    clock_t begin_generating_time = clock ();
    if (type == GS_EIGEN || type == LU_EIGEN) {
      sg = new SparseGenerator<double>(i);
    } else {
      g = new Generator (i);
    }
    clock_t end_generating_time = clock ();

    // save measurement to measurements structure
    measurements->generator_measurements[1][i-min_agents_count] = (double)(end_generating_time - begin_generating_time) / CLOCKS_PER_SEC;
    // transfer generated structured to MyMatrix/MySparseMatrix object (by pointers -> in almost no time)
    if (type == GS_EIGEN || type == LU_EIGEN) {
      sm = new MySparseMatrix<double> (sg->get_cases_count (), sg->get_matrix (), sg->get_matrix_vector ());
    } else {
      m = new MyMatrix<double> (g->get_cases_count (), g->get_matrix (), g->get_matrix_vector ());
    }

    // save matrix size to the data structure
    if (type == GS_EIGEN || type == LU_EIGEN) {
      measurements->calculation_measurements[0][i-min_agents_count] = sg->get_cases_count ();
      measurements->generator_measurements[0][i-min_agents_count] = sg->get_cases_count ();
    } else {
      measurements->calculation_measurements[0][i-min_agents_count] = g->get_cases_count ();
      measurements->generator_measurements[0][i-min_agents_count] = g->get_cases_count ();
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

    // save result to the data structure
    measurements->calculation_measurements[1][i-min_agents_count] = (double)(end_calculation_time - begin_calculation_time) / CLOCKS_PER_SEC;

    // clear and free memory
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

polynomial_t *
find_polynomial (measurement_t *measure, int polynomial)
{
  polynomial_t *result = new polynomial_t;

  Approximation<double> ap = Approximation<double>(measure->calculation_measurements[0], measure->calculation_measurements[1], measure->size, polynomial);
  result->vector = ap.run ();
  result->size   = polynomial + 1;

  return result;
}

int main (int argc, char *argv[])
{
  // Partial Gaussian
  measurement_t *gaussian_measurement = run_measurement (G, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gaussian_polynomial   = find_polynomial (gaussian_measurement, DEFAULT_G_POLYNOMIAL);

  delete_polynomial  (gaussian_polynomial);
  delete_measurement (gaussian_measurement);

  // Partial Gaussian for Sparse Matrices
  measurement_t *gaussian_sparse_measurement = run_measurement (G, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gaussian_sparse_polynomial   = find_polynomial (gaussian_sparse_measurement, DEFAULT_G_SPARSE_POLYNOMIAL);

  delete_polynomial  (gaussian_sparse_polynomial);
  delete_measurement (gaussian_sparse_measurement);

  // Gauss-Seidel with 1e-10 precision
  measurement_t *gauss_seidel_measurement = run_measurement (GS_1E10, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gauss_seidel_polynomial   = find_polynomial (gauss_seidel_measurement, DEFAULT_GS_1E10_POLYNOMIAL);

  delete_polynomial  (gauss_seidel_polynomial);
  delete_measurement (gauss_seidel_measurement);

  // Gauss-Seidel with 1e-10 precision (Sparse implementation)
  measurement_t *gs_eigen_measurement = run_measurement (GS_1E10, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gs_eigen_polynomial   = find_polynomial (gs_eigen_measurement, DEFAULT_GS_1E10_POLYNOMIAL);

  delete_polynomial  (gs_eigen_polynomial);
  delete_measurement (gs_eigen_measurement);

  // SparseLU from Eigen library
  measurement_t *lu_eigen_measurement = run_measurement (LU_EIGEN, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *lu_eigen_polynomial   = find_polynomial (lu_eigen_measurement, DEFAULT_LU_EIGEN_POLYNOMIAL);

  delete_polynomial  (lu_eigen_polynomial);
  delete_measurement (lu_eigen_measurement);
  return EXIT_SUCCESS;
}