#include <iostream>

#include "Server.h"

using namespace std;

int main(int argc, char ** argv)
{
  try
    {
      Server server(argc,argv);
      server.run();
    }
  catch (Exception * e)
    {
      cout << e->toString() << endl;
      delete e;
    }
  return 0;
}
