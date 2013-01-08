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
    throw new Exception("Too few arguments");

  individuals.push_back(Individual(&graph));
  maxIndividuals = 10;
}

Dispatcher::~Dispatcher()
{
  for(int i = 0; i < MAX_RECORDS; i++)
    if(records[i])
      delete records[i];
}

string Dispatcher::interpret(string query)
{
  stringstream ss;
  ss << query;

  string command;
  ss >> command;

  if(command == "exit")
    return "";

  if(command == "graph")
    {
      ss >> command;

      if(command == "n")
	return Utils::int2str(this->graph.getN());

      if(command == "dst")
	{
	  int a, b;
	  ss >> a >> b;
	  return Utils::int2str(graph.getDistance(a,b));
	}
    }

  if(command == "ind")
    {
      ss >> command;

      if(command == "n")
	return Utils::int2str(individuals.size());

      if(command == "best")
	return Utils::int2str(individuals.front().getRate());

      if(command == "ls")
	{
	  string out = "";
	  for(list<Individual>::iterator i = individuals.begin(); i != individuals.end(); i++)
	    out += Utils::int2str(i->getRate()) + "\n";
	  return out;
	}

      if(command == "max")
	{
	  ss >> command;

	  if(command == "set")
	    {
	      int max;
	      ss >> max;
	      if(max > 0)
		maxIndividuals = max;

	      return " ";
	    }

	  if(command == "get")
	    return Utils::int2str(maxIndividuals);
	}

      if(command == "new")
	{
	  Individual tmp(&graph);
	  individuals.push_back(tmp);
	  refreshIndividuals();

	  return Utils::int2str(tmp.getRate());
	}
    }

  if(command == "clis")
    {
      ss >> command;

      if(command == "n")
	{
	  int count = 0;
	  for(int i = 0; i < MAX_RECORDS; i++)
	    if(records[i])
	      count++;
	  return Utils::int2str(count);
	}

      if(command == "ls")
	{
	  string out = "Connected clients:\n\n";
	  for(int i = 0; i < MAX_RECORDS; i++)
	    if(records[i])
	      out += "[" + Utils::int2str(i) + "]\n" + records[i]->toString() + "\n";

	  return out;
	}

      if(command == "def")
	{
	  ss >> command;

	  if(command == "set")
	    {
	      int val;
	      ss >> command >> val;

	      if(command == "frq")
		{
		  if(val > 0)
		    defaults.setFrequence(val);

		  return " ";
		}
	      if(command == "mut")
		{
		  if(val >= 0 && val <= 100)
		    defaults.setMutations(val);

		  return " ";
		}
	      if(command == "pop")
		{
		  if(val > 0)
		    defaults.setPopulation(val);

		  return " ";
		}
	      if(command == "stp")
		{
		  if(val > 0)
		    defaults.setStartPopulation(val);

		  return " ";
		}
	    }

	  if(command == "get")
	    {
	      ss >> command;

	      if(command == "frq")
		return Utils::int2str(defaults.getFrequence());
	      if(command == "mut")
		return Utils::int2str(defaults.getMutations());
	      if(command == "pop")
		return Utils::int2str(defaults.getPopulation());
	      if(command == "stp")
		return Utils::int2str(defaults.getStartPopulation());
	    }

	  return this->defaults.toString();
	}

      if(command == "all")
	{
	  ss >> command;

	  if(command == "set")
	    {
	      int val;
	      ss >> command >> val;

	      if(command == "frq")
		{
		  if(val > 0)
		    for(int i = 0; i < MAX_RECORDS; i++)
		      if(records[i])
			records[i]->setFrequence(val);

		  return " ";
		}
	      if(command == "mut")
		{
		  if(val >= 0 && val <= 100)
		    for(int i = 0; i < MAX_RECORDS; i++)
		      if(records[i])
			records[i]->setMutations(val);

		  return " ";
		}
	      if(command == "pop")
		{
		  if(val > 0)
		    for(int i = 0; i < MAX_RECORDS; i++)
		      if(records[i])
			records[i]->setPopulation(val);

		  return " ";
		}
	      if(command == "stp")
		{
		  if(val > 0)
		    for(int i = 0; i < MAX_RECORDS; i++)
		      if(records[i])
			records[i]->setStartPopulation(val);

		  return " ";
		}
	    }

	  string out = "Connected clients:\n\n";
	  for(int i = 0; i < MAX_RECORDS; i++)
	    if(records[i])
	      out += "[" + Utils::int2str(i) + "]\n" + records[i]->toString() + "\n";

	  return out;
	}
    }

  if(command == "cli")
    {
      int cid;
      ss >> cid >> command;
      if(cid < 0 || MAX_RECORDS <= cid || !records[cid])
	return "Client doesn't exists";

      if(command == "set")
	{
	  int val;
	  ss >> command >> val;

	  if(command == "frq")
	    {
	      if(val > 0)
		records[cid]->setFrequence(val);

	      return " ";
	    }
	  if(command == "mut")
	    {
	      if(val >= 0 && val <= 100)
		records[cid]->setMutations(val);

	      return " ";
	    }
	  if(command == "pop")
	    {
	      if(val > 0)
		records[cid]->setPopulation(val);

	      return " ";
	    }
	  if(command == "stp")
	    {
	      if(val > 0)
		records[cid]->setStartPopulation(val);

	      return " ";
	    }
	}

      if(command == "get")
	{
	  ss >> command;

	  if(command == "frq")
	    return Utils::int2str(records[cid]->getFrequence());
	  if(command == "mut")
	    return Utils::int2str(records[cid]->getMutations());
	  if(command == "pop")
	    return Utils::int2str(records[cid]->getPopulation());
	  if(command == "stp")
	    return Utils::int2str(records[cid]->getStartPopulation());
	}

      return records[cid]->toString();
    }

  return "Wrong command";
}

string Dispatcher::request(int id, string query)
{
  if(!records[id])
    records[id] = new Record(defaults);

  if(query == "")		// disconnected
    {
      delete records[id];
      records[id] = NULL;
    }
  if(query == "MAP")		// map
    return graph.toString();
  if(query.substr(0,3) == "IND") // individual
    {
      stringstream ss;
      int n;

      ss << query.substr(4);
      ss >> n;
      int ord[n];
      for(int i = 0; i < n; i++)
	ss >> ord[i];

      individuals.push_back(Individual(n,&this->graph,ord));
      refreshIndividuals();

      return individuals.front().toString();
    }
  if(query == "BRT")		// actual best rate
    return Utils::int2str(individuals.front().getRate());
  if(query == "BST")		// actual best tour
    return individuals.front().toString();
  if(query == "FRQ")		// frequence
    return Utils::int2str(records[id]->getFrequence());
  if(query == "MUT")		// mutations
    return Utils::int2str(records[id]->getMutations());
  if(query == "POP")		// population
    return Utils::int2str(records[id]->getPopulation());
  if(query == "STP")		// start population
    return Utils::int2str(records[id]->getStartPopulation());

  return "-1";			// wrong command
}

void Dispatcher::refreshIndividuals()
{
  individuals.sort();

  while(individuals.size() > (unsigned int)maxIndividuals)
    individuals.pop_back();
}
