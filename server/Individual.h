#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <stdlib.h>
#include <utility>

#include "Graph.h"

class Individual
{
 protected:
  int n;
  int * ord;
  long long rate;
  Graph * graph;
  void eval();
 public:
  Individual(Graph * graph);
  Individual(int n, Graph * graph, int * ord);
  Individual(const Individual & individual);
  ~Individual();
  bool operator<(const Individual & individual) const;
  virtual std::pair<Individual,Individual> crossingOver(Individual & other);
  virtual void mutate();
  long long getRate();
  std::string toString();
  void shuffle();
};

#endif
