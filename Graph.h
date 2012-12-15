#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "Exception.h"

class Graph
{
  int n;
  int * x;
  int * y;
  void setVertex(int v, int x, int y);
public:
  Graph();
  ~Graph();
  void read();
  void read(std::string fileName);
  int getDistance(int v1, int v2);
};

#endif
