#include "Box.h"

Box::Box(Individual * individual)
{
  this->individual = individual;
}

Box::~Box()
{
}

bool Box::operator<(const Box & box) const
{
  return this->individual->getRate() < box.individual->getRate();
}
