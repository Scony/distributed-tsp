#include "TspServer.h"

#define BUFFER 255

using namespace std;

TspServer::TspServer(int argc, char ** argv, Dispatcher * dispatcher) :
  Server(argc,argv)
{
  this->dispatcher = dispatcher;
}

TspServer::~TspServer()
{
}

void TspServer::run()
{
  char buff[BUFFER];
  int oaddrlen = sizeof(oaddr);
  if(listen(sd,99) == -1)
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
	  int re = read(0,buff,BUFFER);
	  if(re == 0)
	    {
	      fds[0] = 0;
	      continue;
	    }
	  buff[re-1] = '\0';
	  printf("#0: %s\n",buff);
	  if(!dispatcher->interpret(buff))
	    break;
	}
      if(FD_ISSET(sd,&rfds))
	{
	  int ad = accept(sd,(struct sockaddr *)&oaddr,(unsigned int*)&oaddrlen);
	  if(ad == -1)
	    throw new Exception("Accept fail");
	  printf("New connection #%d\n",ad);
	  fds[ad] = 1;
	  string re = dispatcher->request(ad,"MAP");
	  write(ad,re.c_str(),re.length());
	}
      for(int i = 3; i < 1024; i++)
	if(i != sd && FD_ISSET(i,&rfds))
	  {
	    memset(buff,'\0',BUFFER);
	    int ed = read(i,buff,BUFFER);
	    if(ed==0)
	      {
		close(i);
		fds[i] = 0;
		printf("#%d: disconnected.",i);
		buff[ed-1] = '\0';
		string re = dispatcher->request(i,buff);
		write(i,re.c_str(),re.length());
		continue;
	      }
	    printf("#%d: %s\n",i,buff);
	    buff[ed-1] = '\0';
	    string re = dispatcher->request(i,buff);
	    write(i,re.c_str(),re.length());
	  }
    }
}
