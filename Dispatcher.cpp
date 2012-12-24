#include "Dispatcher.h"

using namespace std;

string int2str(int var)
{
  char buff[16];
  sprintf(buff,"%d",var);
  return string(buff);
}

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

string Dispatcher::interpret(string query)
{
  // cout << "::" << query << "::" << endl;
  if(query == "test")
    return int2str(graph.getDistance(1,10));
  if(query == "get clients")
    {
      int count = 0;
      for(int i = 0; i < MAX_RECORDS; i++)
	if(records[i])
	  count++;
      return int2str(count);
    }
  return "Wrong command";
}

string Dispatcher::request(int id, string query)
{
  if(!records[id])
    records[id] = new Record();

  // cout << "::" << query << "::" << endl;

  if(query == "MAP")		// map
    return graph.toString();
  if(query.substr(0,3) == "IND") // individual
    {
      //read given ind
      return individuals.front().toString();
    }
  if(query == "FRQ")		// frequence
    return int2str(records[id]->getFrequence());
  if(query == "MUT")		// mutations
    return int2str(records[id]->getMutations());
  if(query == "POP")		// population
    return int2str(records[id]->getPopulation());

  return "WCM";			// wrong command
}
