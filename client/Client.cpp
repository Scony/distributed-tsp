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
  memset(buff,'\0',BUFFER);

  if(query != "INIT")
    {
      query = Utils::int2str(query.length()) + " " + query;
      write(sd,query.c_str(),query.length());
    }

  int bytes = read(sd,buff,BUFFER-1);
  if(bytes == 0)
    throw new Exception("Disconnected");
  unsigned int contLen;
  sscanf(buff,"%d",&contLen);
  string out = string(buff);

  while((unsigned int)bytes != contLen + Utils::int2str(contLen).length() + 1)
    {
      memset(buff,'\0',BUFFER);
      int tmp = read(sd,buff,BUFFER-1);
      if(tmp == 0)
	throw new Exception("Disconnected");
      bytes += tmp;
      out += string(buff);
    }

  return out.substr(Utils::int2str(contLen).length()+1);
}
