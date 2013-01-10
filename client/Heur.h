#ifndef HEUR_H
#define HEUR_H

#include <utility>
#include <set>

#include "Individual.h"

class Heur : public Individual
{
  int * stick;
  void ord2stick();
  void stick2ord();
 public:
  Heur(Graph * graph);
  Heur(std::string individual, Graph * graph);
  Heur(int n, Graph * graph, int * ord);
  Heur(const Heur & heur);
  Heur(const Individual & ind);
  ~Heur();
  std::pair<Individual*,Individual*> crossingOver(Individual & x);
  void mutate();
};

#endif
