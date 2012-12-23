#ifndef RECORD_H
#define RECORD_H

class Record
{
  int frequence;
  int mutations;
  int population;
 public:
  Record();
  ~Record();
  void setFrequence(int frequence);
  void setMutations(int mutations);
  void setPopulation(int population);
  int getFrequence();
  int getMutations();
  int getPopulation();
};

#endif
