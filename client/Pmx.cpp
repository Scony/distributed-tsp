#include "Pmx.h"

using namespace std;

int randEx(int range_min, int range_max)
{
  int tmp_range;
  if ( range_max >= range_min ) range_max -= range_min;
  else
    {
      tmp_range = range_min - range_max;
      range_min = range_max;
      range_max = tmp_range;
    }
  return (int)(range_max ? range_min + rand() / (RAND_MAX + 1.0) * (double) (range_max + 1) : range_min);
}

void swap(int & a, int & b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

// Pmx::Pmx()
// {
// }

// Pmx::~Pmx()
// {
// }

pair<Individual,Individual> crossingOver(Individual & x)
{
  int l = randEx(1,n-1), r = randEx(1,n-1);
  if(l>r)
    swap(l,r);
  Pmx a(n,this->graph);
  Pmx b(n,this->graph);
  int hashA[n], hashB[n];
  for(int i = 0; i < n; i++)
    {
      hashA[i] = -1;
      hashB[i] = -1;
    }
  for(int i = l; i <= r; i++)
    {
      a.ord[i] = x.ord[i];
      b.ord[i] = ord[i];
      hashA[x.ord[i]] = ord[i];
      hashB[ord[i]] = x.ord[i];
    }
  for(int i = 0; i < l; i++)
    {
      if(hashA[ord[i]]==-1)
	a.ord[i] = ord[i];
      else
	{
	  a.ord[i] = hashA[ord[i]];
	  while(hashA[a.ord[i]]!=-1)
	    a.ord[i] = hashA[a.ord[i]];
	}
      if(hashB[x.ord[i]]==-1)
	b.ord[i] = x.ord[i];
      else
	{
	  b.ord[i] = hashB[x.ord[i]];
	  while(hashB[b.ord[i]]!=-1)
	    b.ord[i] = hashB[b.ord[i]];
	}
    }
  for(int i = r + 1; i < n; i++)
    {
      if(hashA[ord[i]]==-1)
	a.ord[i] = ord[i];
      else
	{
	  a.ord[i] = hashA[ord[i]];
	  while(hashA[a.ord[i]]!=-1)
	    a.ord[i] = hashA[a.ord[i]];
	}
      if(hashB[x.ord[i]]==-1)
	b.ord[i] = x.ord[i];
      else
	{
	  b.ord[i] = hashB[x.ord[i]];
	  while(hashB[b.ord[i]]!=-1)
	    b.ord[i] = hashB[b.ord[i]];
	}
    }
  a.eval();
  b.eval();
  return pair<Individual,Individual>(a,b);
}

void mutate()
{
  int a = randEx(1,n-1), b = randEx(1,n-1);
  if(a<b)
    inv(a,b);
  else
    inv(b,a);
  eval();
}
