#include <iostream>

#include "Client.h"
#include "Evolution.h"
#include "Exception.h"

using namespace std;

int main(int argc, char ** argv)
{
  try
    {
      Client client(argc,argv);
      cout << client.request("INIT");
      // Evolution evolution(argc,argv,&client);
      // evolution.run();
    }
  catch (Exception * e)
    {
      cout << e->toString() << endl;
      delete e;
    }
  return 0;
}
