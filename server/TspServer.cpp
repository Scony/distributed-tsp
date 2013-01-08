#include "TspServer.h"

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
      if(select(1024,&rfds,NULL,NULL,NULL) == -1)
	throw new Exception("Select fail");

      if(FD_ISSET(0,&rfds))
	{
	  int bytes = read(0,buff,BUFFER);
	  if(bytes == 0)
	    {
	      fds[0] = 0;
	      continue;
	    }
	  buff[bytes-1] = '\0';
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
	  printf("#%d connected\n",ad);
	  fds[ad] = 1;

	  string re = dispatcher->request(ad,"MAP");
	  re = Utils::int2str(re.length()) + " " + re;
	  write(ad,re.c_str(),re.length());
	}

      for(int i = 3; i < 1024; i++)
	if(i != sd && FD_ISSET(i,&rfds))
	  {
	    memset(buff,'\0',BUFFER);
	    int bytes = read(i,buff,BUFFER-1);
	    if(bytes == 0 || bytes == -1)
	      {
		close(i);
		fds[i] = 0;
		printf("#%d: disconnected\n",i);
		dispatcher->request(i,string(buff));
		continue;
	      }
	    unsigned int contLen;
	    sscanf(buff,"%d",&contLen);
	    string out = string(buff).substr(Utils::int2str(contLen).length()+1);

	    if(out.length() > 20)
	      printf("#%d: %s...\n",i,out.substr(0,20).c_str());
	    else
	      printf("#%d: %s\n",i,out.c_str());

	    while((unsigned int)bytes != contLen + Utils::int2str(contLen).length() + 1)
	      {
		memset(buff,'\0',BUFFER);
		bytes += read(i,buff,BUFFER-1);
		out += string(buff);
	      }

	    if(out[out.length()-1] == '\n')
	      out = out.substr(0,out.length()-1);

	    try
	      {
		string re = dispatcher->request(i,out);
		re = Utils::int2str(re.length()) + " " + re;
		write(i,re.c_str(),re.length());
	      }
	    catch(Exception * e)
	      {
		printf("%s\n",e->toString().c_str());
		delete e;

		close(i);
		fds[i] = 0;
		printf("#%d: disconnected\n",i);
		dispatcher->request(i,string(buff));
	      }
	  }
    }
}
