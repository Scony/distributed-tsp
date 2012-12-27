#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "Graph.h"
#include "Exception.h"

typedef struct sockaddr_in sockaddr_in;

#define BUFFER 255

class Client
{
 protected:
  int port;
  int sd;
  sockaddr_in servaddr;
 public:
  Client(int argc, char ** argv);
  ~Client();
  std::string request(std::string query);
};

#endif
