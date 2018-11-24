/*
 *  This file is part of 02-gauss task.
 * 
 *  src/gauss.cc
 *  Grams, Stanislaw <sgrams@fmdx.pl>
 *  Jezierski, Maciej <maciejjezierski4@gmail.com>
 *  Korczakowski, Juliusz <iuliuszkor@gmail.com>
 */
#include "gauss.hh"
// constructors and deconstructors
MyType::MyType () {
  mpq_init (this->value);
  mpq_canonicalize (this->value);
}

MyType::MyType (const int set)
{
  mpq_init (this->value);
  mpq_set_si (this->value, set, 1);
  mpq_canonicalize (this->value);
}

MyType::MyType (const float set)
{
  mpq_init (this->value);
  mpq_set_d (this->value, (double) set);
  mpq_canonicalize (this->value);
}

MyType::MyType (const double set)
{
  mpq_init (this->value);
  mpq_set_d (this->value, set);
  mpq_canonicalize (this->value);
}

MyType::MyType (const MyType &set)
{
  mpq_init (this->value);
  mpq_set (this->value, set.value);
  mpq_canonicalize (this->value);
}

MyType::~MyType ()
{
  mpq_clear (this->value);
}

// overloading mathematical operators
void
MyType::operator = (const int equ)
{
  mpq_set_si (this->value, equ, 1);
  mpq_canonicalize (this->value);
}

void
MyType::operator = (const float equ)
{
  mpq_set_d (this->value, (double) equ);
  mpq_canonicalize (this->value);
}

void
MyType::operator = (const double equ)
{
  mpq_set_d (this->value, equ);
  mpq_canonicalize (this->value);
}

void
MyType::operator = (const MyType &equ)
{
  mpq_set (this->value, equ.value);
  mpq_canonicalize (this->value);
}

MyType
MyType::operator + (const MyType &add)
{
  MyType ret;
  mpq_add (ret.value, this->value, add.value);
  mpq_canonicalize (ret.value);
  return ret;
}

MyType
MyType::operator - (const MyType &sub)
{
  MyType ret;
  mpq_sub (ret.value, this->value, sub.value);
  mpq_canonicalize (ret.value);
  return ret;
}

MyType
MyType::operator * (const MyType &mul)
{
  MyType ret;
  mpq_mul (ret.value, this->value, mul.value);
  mpq_canonicalize (ret.value);
  return ret;
}

MyType
MyType::operator / (const MyType &div)
{
  MyType ret;
  mpq_div (ret.value, this->value, div.value);
  mpq_canonicalize (ret.value);
  return ret;
}

void
MyType::operator += (const MyType &adds)
{
  MyType mt = *this;
  mpq_add (this->value, mt.value, adds.value);
  mpq_canonicalize (this->value);
}

void
MyType::operator -= (const MyType &subs)
{
  MyType mt = *this;
  mpq_sub (this->value, mt.value, subs.value);
  mpq_canonicalize (this->value);
}

void
MyType::operator *= (const MyType &muls)
{
  MyType mt = *this;
  mpq_mul (this->value, mt.value, muls.value);
  mpq_canonicalize (this->value);
}

void
MyType::operator /= (const MyType &divs)
{
  MyType mt = *this;
  mpq_div (this->value, mt.value, divs.value);
  mpq_canonicalize (this->value);
}

// overloading boolean operators
bool
MyType::operator <  (const MyType &sma)
{
  if (mpq_cmp (this->value, sma.value) > 0) {
    return false;
  }
  return true;
}

bool
MyType::operator >  (const MyType &big)
{
  if (mpq_cmp (this->value, big.value) < 0) {
    return false;
  }
  return true;
}

bool
MyType::operator <= (const MyType &soe)
{
  if (mpq_cmp (this->value, soe.value) >= 0) {
    return false;
  }
  return true;
}

bool
MyType::operator >= (const MyType &boe)
{
  if (mpq_cmp (this->value, boe.value) <= 0) {
    return false;
  }
  return true;
}

bool
MyType::operator == (const MyType &equ)
{
  if (!mpq_equal (this->value, equ.value)) {
    return false;
  }
  return true;
}

bool
MyType::operator != (const MyType &inq)
{
  if (!mpq_equal (this->value, inq.value)) {
    return true;
  }
  return false;
}

int
MyType::abs (int x)
{
  if (x < 0)
    return -x;
  return x;
}

float
MyType::abs (float x)
{
  if (x < 0)
    return -x;
  return x;
}

double
MyType::abs (double x)
{
  if (x < 0)
    return -x;
  return x;
}

MyType&
MyType::abs (MyType &x)
{
  mpq_abs (x.value, x.value);
  return x;
}

// overloading i/o
ostream& operator << (ostream &os, const MyType &mt)
{
  os << fixed << mt.value;
  return os;
}