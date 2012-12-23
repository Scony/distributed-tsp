#include "Dispatcher.h"

using namespace std;

Dispatcher::Dispatcher(int argc, char ** argv)
{
  for(int i = 0; i < MAX_RECORDS; i++)
    records[i] = NULL;
  if(argc > 2)
    graph.read(argv[2]);
  else if(argc > 1)
    graph.read(argv[1]);
  else
    throw new Exception("Input file not specified");

  individuals.push_back(Individual(&graph));
}

Dispatcher::~Dispatcher()
{
  for(int i = 0; i < MAX_RECORDS; i++)
    if(records[i])
      delete records[i];
}

bool Dispatcher::interpret(string query)
{
  cout << "::" << query << "::" << endl;
  if(query=="lol")
    cout << graph.getDistance(1,10);
  return query == "exit" ? false : true;
}

string Dispatcher::request(int id, string query)
{
  if(!records[id])
    records[id] = new Record();
  cout << "::" << query << "::" << endl;
  if(query=="MAP")
    return graph.toString();
  if(query=="IND")
    return individuals.front().toString();
  return "some re";
}
