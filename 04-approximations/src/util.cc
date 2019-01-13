/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/util.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "util.hh"

namespace
Util {
  void
  print_progressbar (int percentage)
  {
    int left_padding  = (int)((double) percentage/100.0 * (double)PROGRESSBAR_WIDTH);
    int right_padding = PROGRESSBAR_WIDTH - left_padding;

    std::printf ("\r%3d%% [%.*s%*s]", percentage, left_padding, PROGRESSBAR_STRING, right_padding, "");
    std::fflush (stdout);
  }

  void
  save_findings_to_file (measurement_t *gaussian_measurement, double *calculation_approximations,
                        double *generator_approximations, std::string filepath)
  {
    std::ofstream output_file;
    output_file.open (filepath);
    for (int i = 0; i < gaussian_measurement->size; ++i)
    {
      Result *r = new Result ();
      output_file << std::fixed;

      r->x        = gaussian_measurement->calculation_measurements[0][i];
      
      r->fx       = calculation_approximations[i];
      r->time     = gaussian_measurement->calculation_measurements[1][i];
      r->abs_err  = abs (r->fx - r->time);
      r->rel_err  = abs (1 - (r->fx / r->time));
      
      r->gfx      = generator_approximations[i];
      r->gtime    = gaussian_measurement->generator_measurements[1][i];
      r->gabs_err = abs (r->gfx - r->gtime);
      r->grel_err = abs (1 - (r->gfx / r->gtime));
      
      output_file.precision (1);
      output_file << r->x   << ",";
      output_file.precision (18);
      output_file << r->fx  << "," << r->time  << "," << r->abs_err  << "," << r->rel_err  << ",";
      output_file << r->gfx << "," << r->gtime << "," << r->gabs_err << "," << r->grel_err << "\n";
      delete r;
    }

    output_file.close ();
  }
  unsigned int
  calculate_newton (unsigned int n, unsigned int k)
  {
    unsigned int ret = 1;
    
    if (n == k || !k) {
      return 1;
    }

    for (unsigned int i = 1 ; i <= k; ++i)
    {
      ret = ret * (n - i + 1) / i;
    }
    return ret;
  }
}