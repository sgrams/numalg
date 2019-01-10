/*
 *  This file is part of 03-population_protocols task.
 * 
 *  src/protocol.cc
 *  Stanislaw Grams <sgrams@fmdx.pl>
 *  Maciej Jezierski <maciejjezierski4@gmail.com>
 *  Juliusz Korczakowski <iuliuszkor@gmail.com>
 */
#include "protocol.hh"
/*
 * Protocol Class
 */
// main constructor for Protocol class
Protocol::Protocol ()
{
  this->all_votes       = 0;
  this->yes_votes       = 0;
  this->no_votes        = 0;
  this->undecided_votes = 0;
}

Protocol::Protocol (int yes_votes, int no_votes, int all_votes)
{
  this->all_votes       = all_votes;
  this->yes_votes       = yes_votes;
  this->no_votes        = no_votes;
  this->undecided_votes = all_votes - yes_votes - no_votes;
}

// getters and setters for Protocol class
int
Protocol::get_yes_votes ()
{
  return this->yes_votes;
}

int
Protocol::get_no_votes ()
{
  return this->no_votes;
}

int
Protocol::get_undecided_votes ()
{
  return this->undecided_votes;
}

int
Protocol::get_all_votes ()
{
  return this->all_votes;
}

void
Protocol::set_yes_votes (int yes_votes)
{
  this->yes_votes = yes_votes;
}

void
Protocol::set_no_votes (int no_votes)
{
  this->no_votes = no_votes;
}

void
Protocol::set_undecided_votes (int undecided_votes)
{
  this->undecided_votes = undecided_votes;
}

void
Protocol::set_all_votes (int all_votes)
{
  this->all_votes = all_votes;
}

/*
 * Agent Class
 */
Agent::Agent ()
{
  this->state = YES;
  this->is_ready = false;
}

Agent::Agent (state_t state)
{
  this->state = state;
  this->is_ready = false;
}

bool
Agent::ready ()
{
  return this->is_ready;
}

void
Agent::make_ready ()
{
  this->is_ready = true;
}

state_t
Agent::get_state ()
{
  return this->state;
}

void
Agent::set_state (state_t state)
{
  this->state = state;
}

void
Agent::change_state (Agent *agent)
{
  if ((this->state == YES && agent->get_state () == UNDECIDED) ||
      (this->state == UNDECIDED && agent->get_state () == YES)) {
    if (this->state == UNDECIDED) {
      this->state = YES;
    } else {
      agent->set_state (YES);
    }
  }

  if ((this->state == NO && agent->get_state () == UNDECIDED) ||
      (this->state == UNDECIDED && agent->get_state () == NO)) {
    if (this->state == UNDECIDED) {
      this->state = NO;
    } else {
      agent->set_state (NO);
    }
  }

  if ((this->state == YES && agent->get_state () == NO) ||
      (this->state == NO && agent->get_state () == YES)) {
    this->state = UNDECIDED;
    agent->set_state (UNDECIDED);
  }
}

/*
 * MonteCarlo Class
 */
MonteCarlo::MonteCarlo (int iterations, int all_agents)
{
  this->iterations = iterations;
  this->all_agents = all_agents;
  int size = 0;
  int yes_votes = 0;
  int no_votes  = 0;

  for (int i = 1; i <= all_agents + 1; i++)
  {
    size += i;
  }
  
  for (int i = 0; i < size; ++i)
  {
    result_vector.push_back (MonteCarlo::run_simulation (yes_votes, no_votes));
    if (yes_votes != all_agents) {
      if (yes_votes + no_votes == all_agents) {
        yes_votes += 1;
        no_votes   = 0;
      } else {
        no_votes  += 1;
      }
    }
  }
}

state_t
MonteCarlo::run_simulation_helper (Agent* simulation_vector)
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr (0, this->all_agents - 1);
  int yes_votes;
  int no_votes;
  int undecided_votes;

  int cnt_yes_votes;
  int cnt_no_votes;
  int cnt_undecided_votes;

  int random_index_1, random_index_2;
  while (true)
  {
    cnt_yes_votes = 0;
    cnt_no_votes  = 0;
    cnt_undecided_votes = 0;

    random_index_1 = distr (eng);
    random_index_2 = distr (eng);
    
    simulation_vector[random_index_1].change_state (&simulation_vector[random_index_2]);

    // count states after simulation
    for (int i = 0; i < this->all_agents; ++i)
    {
      if (simulation_vector[i].get_state () == YES) {
        cnt_yes_votes += 1;
      }
      if (simulation_vector[i].get_state () == NO) {
        cnt_no_votes += 1;
      }
      if (simulation_vector[i].get_state () == UNDECIDED) {
        cnt_undecided_votes += 1;
      }
    }

    yes_votes = cnt_yes_votes;
    no_votes = cnt_no_votes;
    undecided_votes = cnt_undecided_votes;

    if (yes_votes == this->all_agents || no_votes == this->all_agents || undecided_votes == this->all_agents)
    {
      break;
    }
  }
  return simulation_vector[0].get_state ();
}

double
MonteCarlo::run_simulation (int yes_votes, int no_votes)
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr (0, this->all_agents - 1);
  Agent  *simulation_vector;
  state_t simulation_result;
  int     random_index;
  int     undecided_votes;

  int     ret_yes_votes = 0;

  for (int i = 0; i < this->iterations; ++i)
  {
    undecided_votes = this->all_agents - yes_votes - no_votes;
    simulation_vector = new Agent[this->all_agents];
    // prepare simulation vector
    for (int j = 0; j < yes_votes; ++j)
    {
      while (true)
      {
        random_index = distr (eng);
        if (simulation_vector[random_index].ready()) {
          continue;
        }
        simulation_vector[random_index].set_state (YES);
        simulation_vector[random_index].make_ready ();

        break;
      }
    }

    for (int j = 0; j < no_votes; ++j)
    {
      while (true)
      {
        
        random_index = distr (eng);
        if (simulation_vector[random_index].ready()) {
          continue;
        }
        simulation_vector[random_index].set_state (NO);
        simulation_vector[random_index].make_ready ();

        break;
      }
    }

    if (undecided_votes > 0) {
      for (int j = 0; j < undecided_votes; ++j)
      {
        while (true)
        {
          random_index = distr (eng);
          if (simulation_vector[random_index].ready()) {
            continue;
          }
          simulation_vector[random_index].set_state (UNDECIDED);
          simulation_vector[random_index].make_ready ();

          break;
        }
      }
    }

    // simulate voting
    simulation_result = run_simulation_helper (simulation_vector);

    if (simulation_result == YES) {
      ret_yes_votes += 1;
    }

    delete[] simulation_vector;
  }

  return (double)ret_yes_votes / (double)this->iterations;
}

std::vector<double>
MonteCarlo::get_result_vector ()
{
  return this->result_vector;
}