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
    cout << "Usage: ./gauss <options>" << endl;
    cout << "Available options:" << endl;
    cout << "  -h         print this help" << endl;
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
  save_result_vec_to_file (const vector<result_fields_t>&result_vec, string filename)
  {
    std::ofstream output_file;
    output_file.open (filename);
    for (auto i: result_vec)
    {
      output_file.precision (34);
      output_file << fixed;
      output_file << i.matrix_size << ",";
      output_file << i.abs_err << ",";
      output_file << i.abs_err_pg << ",";
      output_file << i.abs_err_fg << ",";
      output_file << i.rel_err << ",";
      output_file << i.rel_err_pg << ",";
      output_file << i.rel_err_fg << ",";
      output_file << i.avg_time << ",";
      output_file << i.avg_time_pg << ",";
      output_file << i.avg_time_fg << endl;
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