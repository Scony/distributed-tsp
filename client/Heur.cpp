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
  Heur x(ind);
  Heur * rslt = new Heur(graph);
  list<int> remain;
  for(int i = 1; i < n; i++)
    remain.push_back(i);
  int actual = randEx(1,remain.size()-1);
  remain.remove(actual);
  rslt->stick[0] = actual;
  for(int i = 1; i < n-1; i++)
    {
      bool flag1 = false, flag2= false;
      for(list<int>::iterator j = remain.begin(); j!=remain.end(); j++)
	{
	  if(*j==stick[actual])
	    flag1 = true;
	  if(*j==x.stick[actual])
	    flag2 = true;
	  if(flag1 && flag2)
	    break;
	}
      if(flag1 && flag2)
	{
	  if(graph->getDistance(actual,stick[actual])<graph->getDistance(actual,x.stick[actual]))
	    {
	      rslt->stick[actual] = stick[actual];
	      actual = stick[actual];
	      remain.remove(actual);
	    } else
	    {
	      rslt->stick[actual] = x.stick[actual];
	      actual = x.stick[actual];
	      remain.remove(actual);
	    }
	} else if(flag1)
	{
	  rslt->stick[actual] = stick[actual];
	  actual = stick[actual];
	  remain.remove(actual);
	} else if(flag2)
	{
	  rslt->stick[actual] = x.stick[actual];
	  actual = x.stick[actual];
	  remain.remove(actual);
	} else
	{
	  //Q max statyczne
	  // int which = remain.front();
	  // int min = graph->getDistance(actual,which);
	  // for(list<int>::iterator j = remain.begin(); j!=remain.end(); j++)
	  //   if(graph->getDistance(actual,*j)<min)
	  //     {
	  // 	which = *j;
	  // 	min = graph->getDistance(actual,*j);
	  //     }
	  // rslt->stick[actual] = which;
	  // actual = which;
	  // remain.remove(actual);
	  //Q dynamiczne
	  /*int q = 1 + floor(remain.size()/5);
	    int tmp[remain.size()];
	    int k = 0;
	    for(list<int>::iterator j = remain.begin(); j!=remain.end(); j++)
	    tmp[k++] = *j;
	    int rands[q];
	    for(int j = 0; j < q; j++)
	    rands[j] = randEx(0,remain.size()-1);
	    int which = tmp[rands[0]];
	    int min = neighbourMatrix[actual][which];
	    for(int j = 1; j < q; j++)
	    if(neighbourMatrix[actual][tmp[rands[j]]]<min)
	    {
	    which = tmp[rands[j]];
	    min = neighbourMatrix[actual][tmp[rands[j]]];
	    }
	    rslt.stick[actual] = which;
	    actual = which;
	    remain.remove(actual);*/
	  //Q ustalane statyczne
	  int q = 5;
	  int tmp[remain.size()];
	  int k = 0;
	  for(list<int>::iterator j = remain.begin(); j!=remain.end(); j++)
	    tmp[k++] = *j;
	  int rands[q];
	  for(int j = 0; j < q; j++)
	    rands[j] = randEx(0,remain.size()-1);
	  int which = tmp[rands[0]];
	  int min = graph->getDistance(actual,which);
	  for(int j = 1; j < q; j++)
	    if(graph->getDistance(actual,tmp[rands[j]])<min)
	      {
		which = tmp[rands[j]];
		min = graph->getDistance(actual,tmp[rands[j]]);
	      }
	  rslt->stick[actual] = which;
	  actual = which;
	  remain.remove(actual);
	  //Q=1 statyczne
	  /*int which = randEx(0,remain.size()-1);
	    int re;
	    for(list<int>::iterator j = remain.begin(); j!=remain.end(); j++)
	    if(which--==0)
	    {
	    re = *j;
	    break;
	    }
	    rslt.stick[actual] = re;
	    actual = re;
	    remain.remove(actual);*/
	}
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
