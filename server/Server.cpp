#include "Server.h"

Server::Server(int argc, char ** argv)
{
  if(argc > 1)
    sscanf(argv[1],"%d",&this->port);
  else
    this->port = 13373;

  for(int i = 0; i < 1024; i++)
    fds[i] = false;

  this->sd = socket(AF_INET,SOCK_STREAM,0);
  if(this->sd == -1)
    throw new Exception("Socket fail");

  int yes = 1;
  setsockopt(this->sd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));

  this->init();
}

Server::~Server()
{
  close(sd);
}

void Server::init()
{
  fds[0] = true;
  fds[this->sd] = true;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(this->port);
  myaddr.sin_addr.s_addr = INADDR_ANY;
  int bd = bind(sd,(struct sockaddr *)&myaddr,sizeof(myaddr));
  if(bd == -1)
    throw new Exception("Bind fail");
}

void Server::run()
{
  char buff[255];
  int oaddrlen = sizeof(oaddr);
  int ld = listen(sd,99);
  if(ld == -1)
    throw new Exception("Listen fail");
  fd_set rfds;
  while(1)
    {
      FD_ZERO(&rfds);
      for(int i = 0; i < 1024; i++)
	if(fds[i])
	  FD_SET(i,&rfds);
      int sc = select(1024,&rfds,NULL,NULL,NULL);
      if(sc == -1)
	throw new Exception("Select fail");
      printf("[%d] ",sc);
      if(FD_ISSET(0,&rfds))
	{
	  memset(buff,'\0',255);
	  int re = read(0,buff,255);
	  if(re==0)
	    {
	      fds[0] = 0;
	      continue;
	    }
	  printf("[%d] ",re);
	  buff[re-1] = '\0';
	  printf("Console: %s\n",buff);
	  if(!strcmp("exit",buff))
	    break;
	}
      if(FD_ISSET(sd,&rfds))
	{
	  printf("New income\n");
	  int ad = accept(sd,(struct sockaddr *)&oaddr,(unsigned int*)&oaddrlen);
	  fds[ad] = 1;
	}
      for(int i = 3; i < 1024; i++)
	if(i != sd && FD_ISSET(i,&rfds))
	  {
	    int ed = read(i,buff,255);
	    if(ed==0)
	      {
		close(i);
		fds[i] = 0;
		printf("fd #%d: disconnected.",i);
	      }
	    else
	      printf("fd #%d: %s\n",i,buff);
	  }
    }
}
