#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>

#include "Exception.h"
#include "Graph.h"
#include "Record.h"

#define MAX_RECORDS 1024

class Dispatcher
{
  Graph graph;
  Record * record[MAX_RECORDS];
 public:
  Dispatcher(int argc, char ** argv);
  ~Dispatcher();
  bool interpret(std::string query);
  std::string request(int id, std::string query);
};

#endif

