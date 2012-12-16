#include "TspServer.h"

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
  char buff[255];
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
	  int re = read(0,buff,255);
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
	  dispatcher->request(ad,"MAP");
	}
      for(int i = 3; i < 1024; i++)
	if(i != sd && FD_ISSET(i,&rfds))
	  {
	    memset(buff,'\0',255);
	    int ed = read(i,buff,255);
	    if(ed==0)
	      {
		close(i);
		fds[i] = 0;
		printf("#%d: disconnected.",i);
		dispatcher->request(i,buff);
		continue;
	      }
	    printf("#%d: %s\n",i,buff);
	    dispatcher->request(i,buff);
	  }
    }
}
