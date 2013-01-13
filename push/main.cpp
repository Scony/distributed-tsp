#include <iostream>
#include <fstream>
#include <time.h>

#include "Client.h"
#include "Individual.h"
#include "Exception.h"
#include "Graph.h"

using namespace std;

int main(int argc, char ** argv)
{
  try
    {
      Client client(argc,argv);
      if(argc < 4)
	throw new Exception("Too few arguments");

      Graph graph(client.request("INIT"));

      ifstream in(argv[3],ifstream::in);
      string strind;
      getline(in,strind);
      Individual readed(strind,&graph);
      client.request("IND " + readed.toString());
    }
  catch (Exception * e)
    {
      cout << e->toString() << endl;
      delete e;
    }
  return 0;
}
