/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/probability.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "probability.hh"

Probability::Probability (int agents_count, int cases_count)
{
  this->agents_count = agents_count;
  this->cases_count = cases_count;
}

double
Probability::get_agents_count ()
{
  return this->agents_count;
}

void
Probability::set_agents_count (int agents_count)
{
  this->agents_count = agents_count;
}

double
Probability::get_cases_count ()
{
  return this->cases_count;
}

void
Probability::set_cases_count (int cases_count)
{
  this->cases_count = cases_count;
}

double
Probability::generate_value (std::vector<Protocol> protocols_vector, int row, int col)
{
  int yes_votes_in_row = protocols_vector[row].get_yes_votes ();
  int no_votes_in_row  = protocols_vector[row].get_no_votes ();
  int undecided_votes_in_row = protocols_vector[row].get_undecided_votes ();

  int yes_votes_in_col = protocols_vector[col].get_yes_votes ();
  int no_votes_in_col  = protocols_vector[col].get_no_votes ();

  if ((yes_votes_in_row == this->agents_count || no_votes_in_row == this->agents_count)
      && row == col)
    {
      return 1.0;
  }

  if (yes_votes_in_row == 0 && no_votes_in_row == 0 && row == col) {
    return 1.0;
  }

  if (yes_votes_in_row == yes_votes_in_col && no_votes_in_row == no_votes_in_col &&
      (yes_votes_in_row > 1 || no_votes_in_row > 1 || undecided_votes_in_row > 1)) {
    return case_undecided_agents (protocols_vector[row]);
  }

  if (yes_votes_in_row + 1 == yes_votes_in_col && no_votes_in_row == no_votes_in_col &&
      yes_votes_in_row > 0 && undecided_votes_in_row > 0) {
    return case_one_undecided_agent (protocols_vector[row], yes_votes_in_row);
  }

  if (yes_votes_in_row == yes_votes_in_col && no_votes_in_row + 1 == no_votes_in_col &&
      yes_votes_in_row > 0 && undecided_votes_in_row > 0) {
    return case_one_undecided_agent (protocols_vector[row], no_votes_in_row);
  }
  
  if (yes_votes_in_row - 1 == yes_votes_in_col && no_votes_in_row - 1 == no_votes_in_col &&
      yes_votes_in_row > 0 && no_votes_in_row > 0) {
    return case_mixed_agents (protocols_vector[row]);
  }

  if (row == col) {
    return -1.0;
  }

  return 0.0;
}

double
Probability::case_undecided_agents (Protocol protocol) {
  double res = -1.0;
  double denominator = (double)Util::calculate_newton (this->agents_count, 2);

  if (protocol.get_yes_votes () > 1) {
    res += (double)Util::calculate_newton (protocol.get_yes_votes (), 2) / denominator;
  }
  if (protocol.get_no_votes () > 1) {
    res += (double)Util::calculate_newton (protocol.get_no_votes (), 2) / denominator;
  }
  if (protocol.get_undecided_votes () > 1) {
    res += (double)Util::calculate_newton (protocol.get_undecided_votes (), 2) / denominator;
  }

  return res;
}

double
Probability::case_one_undecided_agent (Protocol protocol, int condition)
{
  double res = 0.0;
  double denominator = (double)Util::calculate_newton (this->agents_count, 2);

  if (condition > 0 && protocol.get_undecided_votes () > 0) {
    res = (double)(condition * (protocol.get_undecided_votes ())) / denominator;
  }

  return res;
}

double
Probability::case_mixed_agents (Protocol protocol)
{
  double res = 0.0;
  double denominator = (double)Util::calculate_newton (this->agents_count, 2);

  if (protocol.get_yes_votes () > 0 && protocol.get_no_votes () > 0) {
    res = (double)(protocol.get_yes_votes () * protocol.get_no_votes ()) / denominator;
  }

  return res;
}