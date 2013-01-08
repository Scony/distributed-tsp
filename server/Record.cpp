#include "Record.h"

using namespace std;

Record::Record()
{
  this->frequence = 10;
  this->mutations = 10;
  this->population = 15;
  this->startPopulation = 100;
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

void Record::setStartPopulation(int startPopulation)
{
  this->startPopulation = startPopulation;
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

int Record::getStartPopulation()
{
  return this->startPopulation;
}

string Record::toString()
{
  return "Start population: " + Utils::int2str(this->startPopulation) +
    "\nPopulation cut: " + Utils::int2str(this->population) +
    "\nMutation probability: " + Utils::int2str(this->mutations) +
    "\nCommunication frequence: " + Utils::int2str(this->frequence);
}
