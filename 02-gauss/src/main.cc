/*
 *  This file is part of 02-gauss task.
 * 
 *  src/main.cc
 *  Grams, Stanislaw <sgrams@fmdx.pl>
 *  Jezierski, Maciej <maciejjezierski4@gmail.com>
 *  Korczakowski, Juliusz <iuliuszkor@gmail.com>
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <pthread.h>
#include <vector>
#include <string>

#include "gauss.hh"
#include "util.hh"

#define  DEFAULT_MIN_TEST_SIZE        10
#define  DEFAULT_STEP_SIZE            10
#define  DEFAULT_ATTEMPTS_SIZE        10
#define  DEFAULT_ATTEMPTS_MYTYPE_SIZE 5

#define  MAX_THREADS       3
#define  MAX_FLOAT_TESTS   1000
#define  MAX_DOUBLE_TESTS  1000
#define  MAX_MYTYPE_TESTS  100

#define  DEFAULT_FLOAT_TESTS_FILENAME  "float_tests.csv"
#define  DEFAULT_DOUBLE_TESTS_FILENAME "double_tests.csv"
#define  DEFAULT_MYTYPE_TESTS_FILENAME "mytype_tests.csv"

using namespace std;

progressbar_sync_t pst;

void *worker_func0 (void *buffer)
{
  vector<result_fields_t> result_vec;
  for (int size = DEFAULT_MIN_TEST_SIZE; size <= MAX_FLOAT_TESTS; size += DEFAULT_STEP_SIZE)
  {
    result_fields_t result;
    result.matrix_size = size;
    result.abs_err     = 0;
    result.abs_err_pg  = 0;
    result.abs_err_fg  = 0;
    result.rel_err     = 0;
    result.rel_err_pg  = 0;
    result.rel_err_fg  = 0;
    result.avg_time    = 0;
    result.avg_time_pg = 0;
    result.avg_time_fg = 0;
    for (int test = 0; test < DEFAULT_ATTEMPTS_SIZE; ++test)
    {
      MyMatrix<float> *matrix = new MyMatrix<float>(size);
      
      float  *vec_X;
      float  *ret_vec_np;
      float  *ret_vec_pp;
      float  *ret_vec_cp;
      
      //
      // fill matrices with randomized data
      //
      matrix->fill_matrix ();
      matrix->fill_vector_X ();
      matrix->fill_vector_B ();
      
      //
      // set vec_X to result vector
      //
      vec_X = matrix->get_vector_X ();

      //
      // test no pivoting
      //
      clock_t begin_gnp_time = clock ();
      ret_vec_np = matrix->gaussian_no_pivoting ();
      clock_t end_gnp_time = clock ();
      double  diff_gnp_time = (double)(end_gnp_time - begin_gnp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err  += matrix->count_abs_error (vec_X, ret_vec_np, size);
      result.abs_err  /= 2;
      result.rel_err  += matrix->count_rel_error (vec_X, ret_vec_np, size);
      result.rel_err  /= 2;
      result.avg_time += diff_gnp_time;
      result.avg_time /= 2;

      delete[] ret_vec_np;

      //
      // test partial pivoting
      //
      clock_t begin_gpp_time = clock ();
      ret_vec_pp = matrix->gaussian_partial_pivoting ();
      clock_t end_gpp_time = clock ();
      double  diff_gpp_time = (double)(end_gpp_time - begin_gpp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_pg  += matrix->count_abs_error (vec_X, ret_vec_pp, size);
      result.abs_err_pg  /= 2;
      result.rel_err_pg  += matrix->count_rel_error (vec_X, ret_vec_pp, size);
      result.rel_err_pg  /= 2;
      result.avg_time_pg += diff_gpp_time;
      result.avg_time_pg /= 2;

      delete[] ret_vec_pp;

      //
      // test complete pivoting
      //
      clock_t begin_gcp_time = clock ();
      ret_vec_cp = matrix->gaussian_complete_pivoting ();
      clock_t end_gcp_time = clock ();
      double  diff_gcp_time = (double)(end_gcp_time - begin_gcp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_fg  += matrix->count_abs_error (vec_X, ret_vec_cp, size);
      result.abs_err_fg  /= 2;
      result.rel_err_fg  += matrix->count_rel_error (vec_X, ret_vec_cp, size);
      result.rel_err_fg  /= 2;
      result.avg_time_fg += diff_gcp_time;
      result.avg_time_fg /= 2;
      
      delete[] ret_vec_cp;

      //
      // free memory and update progressbar
      //
      delete matrix;
      pst.cur_value += DEFAULT_STEP_SIZE;
      Util::print_progressbar (((double)((double)pst.cur_value / (double)pst.max_value) * 100));
    }
    result_vec.push_back (result);
  }
  Util::save_result_vec_to_file (result_vec, DEFAULT_FLOAT_TESTS_FILENAME);
  result_vec.clear ();
  pthread_exit (NULL);
}

void *worker_func1 (void *buffer)
{
  vector<result_fields_t> result_vec;
  for (int size = DEFAULT_MIN_TEST_SIZE; size <= MAX_DOUBLE_TESTS; size += DEFAULT_STEP_SIZE)
  {
    result_fields_t result;
    result.matrix_size = size;
    result.abs_err     = 0;
    result.abs_err_pg  = 0;
    result.abs_err_fg  = 0;
    result.rel_err     = 0;
    result.rel_err_pg  = 0;
    result.rel_err_fg  = 0;
    result.avg_time    = 0;
    result.avg_time_pg = 0;
    result.avg_time_fg = 0;
    for (int test = 0; test < DEFAULT_ATTEMPTS_SIZE; ++test)
    {
      MyMatrix<double> *matrix = new MyMatrix<double>(size);
      
      double  *vec_X;
      double  *ret_vec_np;
      double  *ret_vec_pp;
      double  *ret_vec_cp;
      
      //
      // fill matrices with randomized data
      //
      matrix->fill_matrix ();
      matrix->fill_vector_X ();
      matrix->fill_vector_B ();
      
      //
      // set vec_X to result vector
      //
      vec_X = matrix->get_vector_X ();

      //
      // test no pivoting
      //
      clock_t begin_gnp_time = clock ();
      ret_vec_np = matrix->gaussian_no_pivoting ();
      clock_t end_gnp_time = clock ();
      double  diff_gnp_time = (double)(end_gnp_time - begin_gnp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err  += matrix->count_abs_error (vec_X, ret_vec_np, size);
      result.abs_err  /= 2;
      result.rel_err  += matrix->count_rel_error (vec_X, ret_vec_np, size);
      result.rel_err  /= 2;
      result.avg_time += diff_gnp_time;
      result.avg_time /= 2;

      delete[] ret_vec_np;

      //
      // test partial pivoting
      //
      clock_t begin_gpp_time = clock ();
      ret_vec_pp = matrix->gaussian_partial_pivoting ();
      clock_t end_gpp_time = clock ();
      double  diff_gpp_time = (double)(end_gpp_time - begin_gpp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_pg  += matrix->count_abs_error (vec_X, ret_vec_pp, size);
      result.abs_err_pg  /= 2;
      result.rel_err_pg  += matrix->count_rel_error (vec_X, ret_vec_pp, size);
      result.rel_err_pg  /= 2;
      result.avg_time_pg += diff_gpp_time;
      result.avg_time_pg /= 2;

      delete[] ret_vec_pp;

      //
      // test complete pivoting
      //
      clock_t begin_gcp_time = clock ();
      ret_vec_cp = matrix->gaussian_complete_pivoting ();
      clock_t end_gcp_time = clock ();
      double  diff_gcp_time = (double)(end_gcp_time - begin_gcp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_fg  += matrix->count_abs_error (vec_X, ret_vec_cp, size);
      result.abs_err_fg  /= 2;
      result.rel_err_fg  += matrix->count_rel_error (vec_X, ret_vec_cp, size);
      result.rel_err_fg  /= 2;
      result.avg_time_fg += diff_gcp_time;
      result.avg_time_fg /= 2;
      
      delete[] ret_vec_cp;

      //
      // free memory and update progressbar
      //
      delete matrix;
      pst.cur_value += DEFAULT_STEP_SIZE;
      Util::print_progressbar (((double)((double)pst.cur_value / (double)pst.max_value) * 100));
    }
    result_vec.push_back (result);
  }
  Util::save_result_vec_to_file (result_vec, DEFAULT_DOUBLE_TESTS_FILENAME);
  result_vec.clear ();
  pthread_exit (NULL);
}

void *worker_func2 (void *buffer)
{
  vector<result_fields_t> result_vec;
  for (int size = DEFAULT_MIN_TEST_SIZE; size <= MAX_MYTYPE_TESTS; size += DEFAULT_STEP_SIZE)
  {
    result_fields_t result;
    result.matrix_size = size;
    result.abs_err     = 0;
    result.abs_err_pg  = 0;
    result.abs_err_fg  = 0;
    result.rel_err     = 0;
    result.rel_err_pg  = 0;
    result.rel_err_fg  = 0;
    result.avg_time    = 0;
    result.avg_time_pg = 0;
    result.avg_time_fg = 0;
    for (int test = 0; test < DEFAULT_ATTEMPTS_MYTYPE_SIZE; ++test)
    {
      MyMatrix<MyType> *matrix = new MyMatrix<MyType>(size);
      
      MyType  *vec_X;
      MyType  *ret_vec_np;
      MyType  *ret_vec_pp;
      MyType  *ret_vec_cp;
      
      //
      // fill matrices with randomized data
      //
      matrix->fill_matrix ();
      matrix->fill_vector_X ();
      matrix->fill_vector_B ();
      
      //
      // set vec_X to result vector
      //
      vec_X = matrix->get_vector_X ();

      //
      // test no pivoting
      //
      clock_t begin_gnp_time = clock ();
      ret_vec_np = matrix->gaussian_no_pivoting ();
      clock_t end_gnp_time = clock ();
      double  diff_gnp_time = (double)(end_gnp_time - begin_gnp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err  += mpq_get_d (matrix->count_abs_error (vec_X, ret_vec_np, size).value);
      result.abs_err  /= 2;
      result.rel_err  += mpq_get_d (matrix->count_rel_error (vec_X, ret_vec_np, size).value);
      result.rel_err  /= 2;
      result.avg_time += diff_gnp_time;
      result.avg_time /= 2;

      delete[] ret_vec_np;

      //
      // test partial pivoting
      //
      clock_t begin_gpp_time = clock ();
      ret_vec_pp = matrix->gaussian_partial_pivoting ();
      clock_t end_gpp_time = clock ();
      double  diff_gpp_time = (double)(end_gpp_time - begin_gpp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_pg  += mpq_get_d (matrix->count_abs_error (vec_X, ret_vec_pp, size).value);
      result.abs_err_pg  /= 2;
      result.rel_err_pg  += mpq_get_d (matrix->count_rel_error (vec_X, ret_vec_pp, size).value);
      result.rel_err_pg  /= 2;
      result.avg_time_pg += diff_gpp_time;
      result.avg_time_pg /= 2;

      delete[] ret_vec_pp;

      //
      // test complete pivoting
      //
      clock_t begin_gcp_time = clock ();
      ret_vec_cp = matrix->gaussian_complete_pivoting ();
      clock_t end_gcp_time = clock ();
      double  diff_gcp_time = (double)(end_gcp_time - begin_gcp_time) / CLOCKS_PER_SEC;
      // calculate absolute and relative errors, and set times to result structure
      result.abs_err_fg  += mpq_get_d (matrix->count_abs_error (vec_X, ret_vec_cp, size).value);
      result.abs_err_fg  /= 2;
      result.rel_err_fg  += mpq_get_d (matrix->count_rel_error (vec_X, ret_vec_cp, size).value);
      result.rel_err_fg  /= 2;
      result.avg_time_fg += diff_gcp_time;
      result.avg_time_fg /= 2;
      
      delete[] ret_vec_cp;

      //
      // free memory and update progressbar
      //
      delete matrix;
      pst.cur_value += DEFAULT_STEP_SIZE;
      Util::print_progressbar (((double)((double)pst.cur_value / (double)pst.max_value) * 100));
    }
    result_vec.push_back (result);
  }
  Util::save_result_vec_to_file (result_vec, DEFAULT_MYTYPE_TESTS_FILENAME);
  result_vec.clear ();
  pthread_exit (NULL);
}

int main (int argc, char *argv[])
{
  int       ret = 0;
  pthread_t threads[MAX_THREADS];

  pst.cur_value = 0;
  pst.max_value +=  (MAX_FLOAT_TESTS * DEFAULT_ATTEMPTS_SIZE);
  pst.max_value += (MAX_DOUBLE_TESTS * DEFAULT_ATTEMPTS_SIZE);
  pst.max_value += (MAX_MYTYPE_TESTS * DEFAULT_ATTEMPTS_MYTYPE_SIZE);

  // create worker for float tests
  ret = pthread_create (&threads[0], NULL, worker_func0, (void *) NULL);
  if (ret) {
    cerr << "Unable to create thread for worker_func0 (float tests): " << ret << endl;
    exit (-1);
  }

  // create worker for double tests
  ret = pthread_create (&threads[1], NULL, worker_func1, (void *) NULL);
  if (ret) {
    cerr << "Unable to create thread for worker_func1 (double tests): " << ret << endl;
    exit (-1);
  }

  // create worker for MyType tests
  ret = pthread_create (&threads[2], NULL, worker_func2, (void *) NULL);
  if (ret) {
    cerr << "Unable to create thread for worker_func2 (MyType tests): " << ret << endl;
    exit (-1);
  }

  pthread_join (threads[0], NULL);
  pthread_join (threads[1], NULL);
  pthread_join (threads[2], NULL);
  
  cout << endl;
  cout << "Results of tests were written to corresponding files:" << endl;
  cout << "  float_tests.csv" << endl;
  cout << "  double_tests.csv" << endl;
  cout << "  mytype_tests.csv" << endl;

  pthread_exit (NULL);
}
