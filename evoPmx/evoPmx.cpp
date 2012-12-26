#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <list>

#define START_POPULATION 100
#define POPULATION 15
#define GENERATIONS 20000
#define MUTATION_B 0
#define MUTATION_T 1
#define MUTATION_E 19

class Coords
{
  int n;
  int * x;
  int * y;
public:
  Coords(int n)
  {
    this->n = n;
    x = new int[n];
    y = new int[n];
  }
  ~Coords()
  {
    delete [] x;
    delete [] y;
  }
  void setCoords(int v, int x, int y)
  {
    this->x[v] = x;
    this->y[v] = y;
  }
  int getDistance(int a, int b)
  {
    return round(sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])));
  }
};

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

void shuffle(int * arr, int n)
{
  for(int i = 1; i < n; i++)
    {
      int k = randEx(1,n-1);
      swap(arr[i],arr[k]);
    }
}

class Individual
{
  int n;
  long long rate;
  int * ord;
  Coords * coords;
  void eval()
  {
    rate = 0;
    for(int i = 1; i < n; i++)
      rate += coords->getDistance(ord[i-1],ord[i]);
    rate += coords->getDistance(ord[n-1],ord[0]);
  }
  void inv(int left, int right)
  {
    if(left<right)
      {
	swap(ord[left],ord[right]);
	inv(left+1,right-1);
      }
  }
public:
  Individual(int n, Coords * coords)
  {
    this->coords = coords;
    this->n = n;
    ord = new int[n];
  }
  Individual(int n, Coords * coords, int * ord)
  {
    this->n = n;
    this->coords = coords;
    this->ord = new int[n];
    for(int i = 0; i < n; i++)
      this->ord[i] = ord[i];
    eval();
  }
  Individual(const Individual & ind)
  {
    n = ind.n;
    rate = ind.rate;
    coords = ind.coords;
    ord = new int[n];
    for(int i = 0; i < n; i++)
      ord[i] = ind.ord[i];
  }
  ~Individual()
  {
    delete [] ord;
  }
  bool operator<(const Individual& x) const
  {
    return rate < x.rate;
  }
  pair<Individual,Individual> crossingOver(Individual & x)
  {
    int l = randEx(1,n-1), r = randEx(1,n-1);
    if(l>r)
      swap(l,r);
    Individual a(n,coords);
    Individual b(n,coords);
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
  long long getRate()
  {
    return rate;
  }
  void print()
  {
    for(int i = 0; i < n; i++)
      printf("%d ",ord[i]);
    printf("[%lld]\n",rate);
  }
};

int main()
{
  //-----------------------------------------------------
  // read graph
  //-----------------------------------------------------
  int n;
  char buffer[255];
  scanf("NAME: %s\n",buffer);
  scanf("COMMENT: %[^\n]\n",buffer);
  scanf("TYPE: %s\n",buffer);
  scanf("DIMENSION: %d\n",&n);
  scanf("%[^\n]\n",buffer);
  scanf("%[^\n]\n",buffer);

  Coords coords(n);

  for(int i = 0; i < n; i++)
    {
      int v, x, y;
      scanf("%d %d %d",&v,&x,&y);
      coords.setCoords(v-1,x,y);
    }
  //-----------------------------------------------------
  //evolution-pathial-representation-pmx-crossing-over
  //-----------------------------------------------------
  list<Individual> population;
  //start population generating
  for(int i = 0; i < START_POPULATION; i++)
    {
      int arr[n];
      for(int j = 0; j < n; j++)
	arr[j] = j;
      shuffle(arr,n);
      population.push_back(Individual(n,&coords,arr));
    }
  //generations loop
  for(int i = 0; i < GENERATIONS; i++)
    {
      //selection (sort + cut)
      population.sort();
      if(i > 0)
	printf("[GENERATION: %d]: %lld\n",i,population.front().getRate());
      while(population.size()>POPULATION)
	population.pop_back();
      //crossing over
      list<Individual> tmp;
      for(list<Individual>::iterator j = population.begin(); j != population.end(); j++)
	for(list<Individual>::iterator k = j; k != population.end(); k++)
	  if(j!=k)
	    {
	      pair<Individual,Individual> tmp2 = j->crossingOver(*k);
	      tmp.push_back(tmp2.first);
	      tmp.push_back(tmp2.second);
	    }
      printf("[NEW_INDIVIDUALS: %d MUTATIONS: ",tmp.size());
      while(!tmp.empty())
        {
	  population.push_back(tmp.front());
	  tmp.pop_front();
        }
      //mutation
      int mutations = 0;
      for(list<Individual>::iterator j = population.begin(); j != population.end(); j++)
	if(randEx(MUTATION_B,MUTATION_E)==MUTATION_T)
	  {
	    j->mutate();
	    mutations++;
	  }
      printf("%d]\n",mutations);
    }
  population.sort();
  Individual min = population.front();
  printf("Best tour: %lld",min.getRate());
  //-----------------------------------------------------
  // end
  //-----------------------------------------------------
  return 0;
}
