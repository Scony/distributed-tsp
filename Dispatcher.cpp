#include "Dispatcher.h"

using namespace std;

Dispatcher::Dispatcher(int argc, char ** argv)
{
  for(int i = 0; i < MAX_RECORDS; i++)
    record[i] = NULL;
  if(argc > 2)
    graph.read(argv[2]);
  else if(argc > 1)
    graph.read(argv[1]);
  else
    throw new Exception("Input file not specified");
}

Dispatcher::~Dispatcher()
{
  for(int i = 0; i < MAX_RECORDS; i++)
    if(record[i])
      delete record[i];
}

bool Dispatcher::interpret(string query)
{
  cout << "::" << query << "::" << endl;
  return query == "exit" ? false : true;
}

string Dispatcher::request(int id, string query)
{
  cout << "::" << query << "::" << endl;
  return "some re";
}
