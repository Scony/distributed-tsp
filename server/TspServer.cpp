#include "TspServer.h"

#define BUFFER 2049

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

  if(listen(sd,128) == -1)
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
	  int rc = read(0,buff,BUFFER);
	  if(rc == 0)
	    {
	      fds[0] = 0;
	      continue;
	    }
	  buff[rc-1] = '\0';
	  printf("#0: %s\n",buff);
	  string re = dispatcher->interpret(buff);
	  if(re == "")
	    break;
	  printf("%s\n",re.c_str());
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
	    string out = "";
	    memset(buff,'\0',BUFFER);
	    int ed = read(i,buff,BUFFER-1);
	    if(ed == 0 || ed == -1)
	      {
		close(i);
		fds[i] = 0;
		printf("#%d: disconnected\n",i);
		buff[ed-1] = '\0';
		dispatcher->request(i,string(buff));
		continue;
	      }
	    out += string(buff);
	    if(out.length() > 20)
	      printf("#%d: %s...\n",i,out.substr(0,20).c_str());
	    else
	      printf("#%d: %s\n",i,out.c_str());
	    while(ed == BUFFER-1)
	      {
		memset(buff,'\0',BUFFER);
		ed = read(i,buff,BUFFER-1);
		out += string(buff);
	      }
	    if(out[out.length()-1] == '\n')
	      out = out.substr(0,out.length()-1);
	    string re = dispatcher->request(i,out);
	    write(i,re.c_str(),re.length());
	  }
    }
}
