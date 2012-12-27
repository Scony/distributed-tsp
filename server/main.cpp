#include <iostream>

#include "TspServer.h"
#include "Dispatcher.h"
#include "Exception.h"

using namespace std;

int main(int argc, char ** argv)
{
  try
    {
      Dispatcher dispatcher(argc,argv);
      TspServer server(argc,argv,&dispatcher);
      server.run();
    }
  catch (Exception * e)
    {
      cout << e->toString() << endl;
      delete e;
    }
  return 0;
}
