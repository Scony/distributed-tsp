#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <string.h>
#include <sstream>
#include <list>

#include "Exception.h"
#include "Graph.h"
#include "Record.h"
#include "Individual.h"
#include "Utils.h"

#define MAX_RECORDS 1024

class Dispatcher
{
  Graph graph;
  Record defaults;
  Record * records[MAX_RECORDS];
  std::list<Individual> individuals;
  int maxIndividuals;
 public:
  Dispatcher(int argc, char ** argv);
  ~Dispatcher();
  std::string interpret(std::string query);
  std::string request(int id, std::string query);
  void refreshIndividuals();
};

#endif

