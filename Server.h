#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include "Exception.h"
#include "Graph.h"

typedef struct sockaddr_in sockaddr_in;

class Server
{
  Graph graph;
  int port;
  int sd;
  bool fds[1024];
  sockaddr_in myaddr;
  sockaddr_in oaddr;
  void init();
 public:
  Server(int argc, char ** argv);
  ~Server();
  void run();
};

#endif
