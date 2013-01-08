#ifndef RECORD_H
#define RECORD_H

#include "Utils.h"

class Record
{
  int frequence;
  int mutations;
  int population;
  int startPopulation;
 public:
  Record();
  ~Record();
  void setFrequence(int frequence);
  void setMutations(int mutations);
  void setPopulation(int population);
  void setStartPopulation(int startPopulation);
  int getFrequence();
  int getMutations();
  int getPopulation();
  int getStartPopulation();
  std::string toString();
};

#endif
