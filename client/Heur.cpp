#include "Heur.h"

using namespace std;

Heur::Heur(Graph * graph) : Individual(graph)
{
  stick = new int[graph->getN()];

  ord2stick();
}

Heur::Heur(string individual, Graph * graph) : Individual(individual,graph)
{
  stick = new int[graph->getN()];

  ord2stick();
}

Heur::Heur(int n, Graph * graph, int * ord) : Individual(n,graph,ord)
{
  stick = new int[n];

  ord2stick();
}

Heur::Heur(const Heur & heur) : Individual(heur)
{
  stick = new int[n];

  for(int i = 0; i < n; i++)
    stick[i] = heur.stick[i];
}

Heur::Heur(const Individual & ind) : Individual(ind)
{
  stick = new int[n];

  ord2stick();
}

Heur::~Heur()
{
  delete [] stick;
}

void Heur::ord2stick()
{
  for(int i = 1; i < n; i++)
    stick[ord[i-1]] = ord[i];
  stick[ord[n-1]] = ord[0];
}

void Heur::stick2ord()
{
  int j = 0;
  for(int i = 0; i < n; i++)
    {
      ord[i] = stick[j];
      j = stick[j];
    }

  eval();
}

pair<Individual*,Individual*> Heur::crossingOver(Individual & ind)
{
  Heur heur(ind);
  Heur * rslt = new Heur(graph);

  set<int> remain;
  for(int i = 1; i < n; i++)
    remain.insert(i);

  int actual = Utils::randEx(1,n-1);
  remain.erase(actual);
  rslt->stick[0] = actual;
  for(int i = 1; i < n-1; i++)
    {
      int a = remain.count(stick[actual]);
      int b = remain.count(heur.stick[actual]);

      if(a && b)
	{
	  if(graph->getDistance(actual,stick[actual]) < graph->getDistance(actual,heur.stick[actual]))
	    {
	      rslt->stick[actual] = stick[actual];
	      actual = stick[actual];
	    } else
	    {
	      rslt->stick[actual] = heur.stick[actual];
	      actual = heur.stick[actual];
	    }
	  remain.erase(actual);
	  continue;
	}

      if(a)
	{
	  rslt->stick[actual] = stick[actual];
	  actual = stick[actual];
	  remain.erase(actual);
	  continue;
	}

      if(b)
	{
	  rslt->stick[actual] = heur.stick[actual];
	  actual = heur.stick[actual];
	  remain.erase(actual);
	  continue;
	}

      int r = Utils::randEx(1,remain.size());
      set<int>::iterator j = remain.begin(); 
      while(--r)
	j++;

      rslt->stick[actual] = *j;
      actual = *j;
      remain.erase(j);
    }
  rslt->stick[actual] = 0;
  rslt->stick2ord();
  rslt->eval();

  Heur * rsltCpy = new Heur(*rslt);

  return pair<Individual*,Individual*>(rslt,rsltCpy);
}

void Heur::mutate()
{
  int a = randEx(0,n-1);
  int b = randEx(0,n-1);

  while(a == b)
    b = randEx(0,n-1);

  for(int i = 0; i < n; i++)
    if(stick[i] == a)
      stick[i] = b;
    else if(stick[i] == b)
      stick[i] = a;

  swap(stick[a],stick[b]);

  stick2ord();
  eval();
}
