#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "Client.h"
#include "Individual.h"
#include "Pmx.h"

class Evolution
{
  Graph graph;
  int startPopulation;
  int population;
  int mutations;
  int frequence;
 public:
  Evolution(int argc, char ** argv, Client * client);
  ~Evolution();
  void run();
};

#endif
