/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/util.hh
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#ifndef _GAUSS_UTIL_H
#define _GAUSS_UTIL_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "matrix.hh"

#define PROGRESSBAR_STRING "#################################################"
#define PROGRESSBAR_WIDTH  50

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
  double *calculation_vector;
  double *generator_vector;
  int size;
} polynomial_t;

class Result {
  public:
    // calculator
    double x = 0.0;
    double fx = 0.0;
    double time = 0.0;
    double abs_err = 0.0;
    double rel_err = 0.0;
    // generator
    double gfx = 0.0;
    double gtime = 0.0;
    double gabs_err = 0.0;
    double grel_err = 0.0;
};

typedef struct progressbar_sync {
  int cur_value = 0;
  int max_value = 0;
} progressbar_sync_t;

namespace Util {
  void
  print_help ();

  void
  print_progressbar (int percentage);

  unsigned int
  calculate_newton (unsigned int n, unsigned int k);

  void
  save_findings_to_file (polynomial_t *polynomial, measurement_t *gaussian_measurement, double *calculation_approximations,
                        double *generator_approximations, std::string filepath);
  double
  extrapolate_generator (polynomial_t *polynomial, int size);
  double
  extrapolate_calculation (polynomial_t *polynomial, int size);
}
#endif // _GAUSS_UTIL_H