#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <iostream>
#include <sstream>
#include <list>

#include "Client.h"
#include "Exception.h"
#include "Box.h"
#include "Pmx.h"

class Evolution
{
  Graph * graph;
  Client * client;
  std::list<Box> population;
  int algorithm;
  int startPopulation;
  int populationCut;
  int mutations;
  int frequence;
 public:
  Evolution(int argc, char ** argv, Client * client);
  ~Evolution();
  void run();
  static int randEx(int range_min, int range_max);
};

#endif
