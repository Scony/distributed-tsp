#include "Client.h"

using namespace std;

Client::Client(int argc, char ** argv)
{
  if(argc < 3)
    throw new Exception("Too few arguments");

  sscanf(argv[2],"%d",&this->port);

  this->servaddr.sin_family = AF_INET;
  this->servaddr.sin_port = htons(this->port);
  this->servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  this->sd = socket(AF_INET,SOCK_STREAM,0);
  if(this->sd == -1)
    throw new Exception("Socket fail");

  if(connect(this->sd,(struct sockaddr *)&this->servaddr,sizeof(this->servaddr)) == -1)
    throw new Exception("Connect fail");
}

Client::~Client()
{
  close(this->sd);
}

string Client::request(string query)
{
  char buff[BUFFER];
  string out = "";

  if(query != "INIT")
    write(sd,query.c_str(),query.length());

  sleep(1); //zmienic na pollowanie az beda dane

  struct pollfd ufds[1];
  ufds[0].fd = this->sd;
  ufds[0].events = POLLIN;

  while(poll(ufds,1,0) && (ufds[0].revents & POLLIN))
    {
      memset(buff,'\0',BUFFER);
      read(sd,buff,BUFFER-1);
      buff[BUFFER-1] = '\0';
      out += string(buff);
    }

  return out;
}
