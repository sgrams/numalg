/*
 *  This file is part of 02-gauss task.
 * 
 *  src/util.cc
 *  Grams, Stanislaw <sgrams@fmdx.pl>
 *  Jezierski, Maciej <maciejjezierski4@gmail.com>
 *  Korczakowski, Juliusz <iuliuszkor@gmail.com>
 */
#include "util.hh"

namespace Util {
  void
  print_help ()
  {
    cout << "Usage: <options>" << endl;
    cout << "Available options:" << endl;
    cout << "  -h         print this help" << endl;
    cout << "  -s <size>  set matrix sizes" << endl;
    cout << "  -t <1/2/3> set types" << endl;
    cout << "  -m <1/2/3> set methods" << endl;
  }
};