/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/gauss.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "gauss.hh"

// overloading i/o
ostream& operator << (ostream &os, const MyType &mt)
{
  os << fixed << mt.value;
  return os;
}
