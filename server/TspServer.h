#ifndef TSPSERVER_H
#define TSPSERVER_H

#include <iostream>

#include "Server.h"
#include "Dispatcher.h"
#include "Utils.h"

class TspServer : public Server
{
  Dispatcher * dispatcher;
 public:
  TspServer(int argc, char ** argv, Dispatcher * dispatcher);
  ~TspServer();
  void run();
};

#endif
