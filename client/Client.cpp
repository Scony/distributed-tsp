#include "Client.h"

using namespace std;

Client::Client(int argc, char ** argv)
{
  if(argc < 3)
    throw new Exception("Too few arguments");

  sscanf(argv[1],"%d",&this->port);

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(this->port);
  servaddr.sin_addr.s_addr = inet_addr(argv[2]);

  this->sd = socket(AF_INET,SOCK_STREAM,0);
  if(this->sd == -1)
    throw new Exception("Socket fail");

  if(connect(sd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
    throw new Exception("Connect fail");
}

Client::~Client()
{
  close(this->sd);
}

string Client::request(string query)
{
  char buff[BUFFER];

  if(query == "INIT")
    {
      read(sd,buff,BUFFER);
      return string(buff);
    }

  return "Not implemented re";  // write n read
}
