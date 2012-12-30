#include <iostream>
#include <time.h>

#include "Client.h"
#include "Evolution.h"
#include "Exception.h"

using namespace std;

int main(int argc, char ** argv)
{
  try
    {
      srand(time(0));
      Client client(argc,argv);
      Evolution evolution(argc,argv,&client);
      evolution.run();
    }
  catch (Exception * e)
    {
      cout << e->toString() << endl;
      delete e;
    }
  return 0;
}
