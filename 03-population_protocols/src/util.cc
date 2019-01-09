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
  print_help ()
  {
    std::cout << "Usage: ./gauss <options>" << std::endl;
    std::cout << "Available options:" << std::endl;
    std::cout << "  -h         print this help" << std::endl;
  }

  void
  print_progressbar (int percentage)
  {
    int left_padding  = (int)((double) percentage/100.0 * (double)PROGRESSBAR_WIDTH);
    int right_padding = PROGRESSBAR_WIDTH - left_padding;

    std::printf ("\r%3d%% [%.*s%*s]", percentage, left_padding, PROGRESSBAR_STRING, right_padding, "");
    std::fflush (stdout);
  }

  void
  save_result_vec_to_file (const std::vector<result_fields_t>&result_vec, std::string filename)
  {
    std::ofstream output_file;
    output_file.open (filename);
    for (auto i: result_vec)
    {
      output_file.precision (34);
      output_file << std::fixed;
      output_file << i.agent_count << ",";

      output_file << i.abs_err_g << ",";
      output_file << i.abs_err_gi << ",";
      output_file << i.abs_err_gs << ",";
      output_file << i.abs_err_gsit << ",";
      output_file << i.abs_err_j << ",";
      output_file << i.abs_err_jit << ",";
      output_file << i.abs_err_mc << ",";

      output_file << i.avg_time_g << ",";
      output_file << i.avg_time_gi << ",";
      output_file << i.avg_time_gs << ",";
      output_file << i.avg_time_gsit << ",";
      output_file << i.avg_time_j << ",";
      output_file << i.avg_time_jit << ",";
      output_file << i.avg_time_mc << std::endl;
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