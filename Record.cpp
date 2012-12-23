#include "Record.h"

Record::Record()
{
  this->frequence = 10;
  this->mutations = 10;
  this->population = 15;
}

Record::~Record()
{
}

void Record::setFrequence(int frequence)
{
  this->frequence = frequence;
}

void Record::setMutations(int mutations)
{
  this->mutations = mutations;
}

void Record::setPopulation(int population)
{
  this->population = population;
}

int Record::getFrequence()
{
  return this->frequence;
}

int Record::getMutations()
{
  return this->mutations;
}

int Record::getPopulation()
{
  return this->population;
}
