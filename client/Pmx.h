#ifndef PMX_H
#define PMX_H

#include <utilities>

#include "Individual.h"

class Pmx : public Individual
{
  //params
 public:
  /* Pmx(); */
  /* ~Pmx(); */
  std::pair<Individual,Individual> crossingOver(Individual & x);
  void mutate;
};

#endif
