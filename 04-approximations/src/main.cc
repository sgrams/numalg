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
#include <cmath>

#include "util.hh"
#include "protocol.hh"
#include "matrix.hh"
#include "sparsematrix.hh"
#include "generator.hh"
#include "sparsegenerator.hh"
#include "probability.hh"
#include "approximation.hh"

#define DEFAULT_GS_EPSILON        0.0000000001 // 1e^-10
#define DEFAULT_SPARSE_GS_EPSILON 0.0000000001 // 1e^-10
#define DEFAULT_MIN_AGENTS_COUNT  3
#define DEFAULT_MAX_AGENTS_COUNT  60

#define DEFAULT_G_POLYNOMIAL        3
#define DEFAULT_G_SPARSE_POLYNOMIAL 2
#define DEFAULT_GS_1E10_POLYNOMIAL  2
#define DEFAULT_GS_EIGEN_POLYNOMIAL 2
#define DEFAULT_LU_EIGEN_POLYNOMIAL 1
#define DEFAULT_100K_LU_EIGEN_CASE  446 // 447 * 448 / 2 == 100128

#define DEFAULT_G_FILEPATH        "gauss.csv"
#define DEFAULT_G_SPARSE_FILEPATH "gauss_sparse.csv"
#define DEFAULT_GS_1E10_FILEPATH  "gs_1e10.csv"
#define DEFAULT_GS_EIGEN_FILEPATH "gs_eigen.csv"
#define DEFAULT_LU_EIGEN_FILEPATH "lu_eigen.csv"
#define DEFAULT_100K_LU_EIGEN_FILEPATH "lu_eigen.csv"
#define DEFAULT_EXTRAPOLATION_FILEPATH "extrapolation.csv"

using namespace std;

void
delete_polynomial (polynomial_t *polynomial)
{
  delete[] polynomial->calculation_vector;
  delete[] polynomial->generator_vector;
  delete polynomial;
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
find_polynomial (measurement_t *measurement, int polynomial)
{
  polynomial_t *result = new polynomial_t;

  Approximation<double> calculation_ap = Approximation<double>(measurement->calculation_measurements[0], measurement->calculation_measurements[1], measurement->size, polynomial);
  Approximation<double> generator_ap = Approximation<double>(measurement->generator_measurements[0], measurement->generator_measurements[1], measurement->size, polynomial);
  
  result->calculation_vector = calculation_ap.run ();
  result->generator_vector   = generator_ap.run ();
  result->size               = polynomial + 1;

  return result;
}

double *
approximation_function_calculation (polynomial_t *polynomial, double *vec_x, int size)
{
  double *result = new double[size];
  for (int i = 0; i < size; ++i)
  {
    double temp = 0.0;
    for (int j = 0; j < polynomial->size; ++j)
    {
      temp += (polynomial->calculation_vector[j] * pow (vec_x[i], j));
    }
    result[i] = temp;
  }

  return result;
}

double *
approximation_function_generator (polynomial_t *polynomial, double *vec_x, int size)
{
  double *result = new double[size];
  for (int i = 0; i < size; ++i)
  {
    double temp = 0.0;
    for (int j = 0; j < polynomial->size; ++j)
    {
      temp += (polynomial->generator_vector[j] * pow (vec_x[i], j));
    }
    result[i] = temp;
  }

  return result;
}

int main (int argc, char *argv[])
{
  int size = DEFAULT_MAX_AGENTS_COUNT - DEFAULT_MIN_AGENTS_COUNT + 1;
  double *calculation_approximations;
  double *generator_approximations;


  // Partial Gaussian
  measurement_t *gaussian_measurement = run_measurement (G, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gaussian_polynomial   = find_polynomial (gaussian_measurement, DEFAULT_G_POLYNOMIAL);
  
  calculation_approximations = approximation_function_calculation (gaussian_polynomial,
                                gaussian_measurement->calculation_measurements[0], size);
  generator_approximations   = approximation_function_generator (gaussian_polynomial,
                                gaussian_measurement->generator_measurements[0], size);
  Util::save_findings_to_file (gaussian_polynomial, gaussian_measurement, calculation_approximations, generator_approximations, DEFAULT_G_FILEPATH);
  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (gaussian_polynomial);
  delete_measurement (gaussian_measurement);


  // Partial Gaussian for Sparse Matrices
  measurement_t *gaussian_sparse_measurement = run_measurement (G, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gaussian_sparse_polynomial   = find_polynomial (gaussian_sparse_measurement, DEFAULT_G_SPARSE_POLYNOMIAL);
  calculation_approximations = approximation_function_calculation (gaussian_sparse_polynomial,
                                gaussian_sparse_measurement->calculation_measurements[0], size);
  generator_approximations   = approximation_function_generator (gaussian_sparse_polynomial,
                                gaussian_sparse_measurement->generator_measurements[0], size);
  Util::save_findings_to_file (gaussian_sparse_polynomial, gaussian_sparse_measurement, calculation_approximations, generator_approximations, DEFAULT_G_SPARSE_FILEPATH);

  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (gaussian_sparse_polynomial);
  delete_measurement (gaussian_sparse_measurement);


  // Gauss-Seidel with 1e-10 precision
  measurement_t *gauss_seidel_measurement = run_measurement (GS_1E10, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gauss_seidel_polynomial   = find_polynomial (gauss_seidel_measurement, DEFAULT_GS_1E10_POLYNOMIAL);
  calculation_approximations = approximation_function_calculation (gauss_seidel_polynomial,
                                gauss_seidel_measurement->calculation_measurements[0], size);
  generator_approximations   = approximation_function_generator (gauss_seidel_polynomial,
                                gauss_seidel_measurement->generator_measurements[0], size);
  Util::save_findings_to_file (gauss_seidel_polynomial, gauss_seidel_measurement, calculation_approximations, generator_approximations, DEFAULT_GS_1E10_FILEPATH);

  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (gauss_seidel_polynomial);
  delete_measurement (gauss_seidel_measurement);

  // Gauss-Seidel with 1e-10 precision (Sparse implementation)
  measurement_t *gs_eigen_measurement = run_measurement (GS_1E10, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *gs_eigen_polynomial   = find_polynomial (gs_eigen_measurement, DEFAULT_GS_1E10_POLYNOMIAL);
  calculation_approximations = approximation_function_calculation (gs_eigen_polynomial,
                                gs_eigen_measurement->calculation_measurements[0], size);
  generator_approximations   = approximation_function_generator (gs_eigen_polynomial,
                                gs_eigen_measurement->generator_measurements[0], size);
  Util::save_findings_to_file (gs_eigen_polynomial, gs_eigen_measurement, calculation_approximations, generator_approximations, DEFAULT_GS_EIGEN_FILEPATH);

  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (gs_eigen_polynomial);
  delete_measurement (gs_eigen_measurement);

  // SparseLU from Eigen library
  measurement_t *lu_eigen_measurement = run_measurement (LU_EIGEN, DEFAULT_MIN_AGENTS_COUNT, DEFAULT_MAX_AGENTS_COUNT);
  polynomial_t *lu_eigen_polynomial   = find_polynomial (lu_eigen_measurement, DEFAULT_LU_EIGEN_POLYNOMIAL);
  calculation_approximations = approximation_function_calculation (lu_eigen_polynomial,
                                lu_eigen_measurement->calculation_measurements[0], size);
  generator_approximations   = approximation_function_generator (lu_eigen_polynomial,
                                lu_eigen_measurement->generator_measurements[0], size);
  Util::save_findings_to_file (lu_eigen_polynomial, lu_eigen_measurement, calculation_approximations, generator_approximations, DEFAULT_LU_EIGEN_FILEPATH);

  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (lu_eigen_polynomial);
  delete_measurement (lu_eigen_measurement);

  // SparseLU 100k x 100k! (446 agents)
  measurement_t *lu_eigen_100k_measurement = run_measurement (LU_EIGEN, DEFAULT_100K_LU_EIGEN_CASE, DEFAULT_100K_LU_EIGEN_CASE);
  polynomial_t *lu_eigen_100k_polynomial   = find_polynomial (lu_eigen_100k_measurement, DEFAULT_LU_EIGEN_POLYNOMIAL);
  
  calculation_approximations = approximation_function_calculation (lu_eigen_100k_polynomial,
                                lu_eigen_100k_measurement->calculation_measurements[0], 1);
  generator_approximations   = approximation_function_generator (lu_eigen_100k_polynomial,
                                lu_eigen_100k_measurement->generator_measurements[0], 1);
  Util::save_findings_to_file (lu_eigen_100k_polynomial, lu_eigen_100k_measurement,
                              calculation_approximations, generator_approximations, DEFAULT_100K_LU_EIGEN_FILEPATH);

  delete[] calculation_approximations;
  delete[] generator_approximations;
  delete_polynomial  (lu_eigen_100k_polynomial);
  delete_measurement (lu_eigen_100k_measurement);

  return EXIT_SUCCESS;
}