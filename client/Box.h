#ifndef BOX_H
#define BOX_H

#include "Individual.h"

struct Box
{
  Individual * individual;
  Box(Individual * individual);
  ~Box();
  bool operator<(const Box & box) const;
};

#endif
