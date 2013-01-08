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
    {
      query = Utils::int2str(query.length()) + " " + query;
      write(sd,query.c_str(),query.length());
    }

  // struct pollfd ufds[1];
  // ufds[0].fd = this->sd;
  // ufds[0].events = POLLIN;
  
  // while(poll(ufds,1,1000) == 0); //wait for data

  int red = read(sd,buff,BUFFER-1);
  int contLen;
  sscanf(buff,"%d",&contLen);
  out += string(buff).substr(Utils::int2str(contLen).length() + 1);

  while((unsigned int)red != contLen + Utils::int2str(contLen).length() + 1)
    {
      memset(buff,'\0',BUFFER);
      red += read(sd,buff,BUFFER-1);
      out += string(buff);
    }

  return out;
}
