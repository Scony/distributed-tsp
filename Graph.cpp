#include "Graph.h"

using namespace std;

Graph::Graph()
{
  this->n = 0;
  this->x = NULL;
  this->y = NULL;
}

Graph::~Graph()
{
  if(this->x && this->y)
    {
      delete [] x;
      delete [] y;
    }
}

void Graph::read()
{
  char buffer[255];
  scanf("NAME: %s\n",buffer);
  scanf("COMMENT: %[^\n]\n",buffer);
  scanf("TYPE: %s\n",buffer);
  scanf("DIMENSION: %d\n",&this->n);
  scanf("%[^\n]\n",buffer);
  scanf("%[^\n]\n",buffer);

  this->x = new int[this->n];
  this->y = new int[this->n];

  for(int i = 0; i < this->n; i++)
    {
      int v, x, y;
      scanf("%d %d %d",&v,&x,&y);
      this->setVertex(v-1,x,y);
    }
}

void Graph::read(string fileName)
{
}

void Graph::setVertex(int v, int x, int y)
{
  if(v < 0 || n <= v)
    throw new Exception("Vertex out of bounds");
  this->x[v] = x;
  this->y[v] = y;
}

int Graph::getDistance(int a, int b)
{
  if(a < 0 || b < 0 || n <= a || n <= b)
    throw new Exception("Vertex out of bounds");
  return round(sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])));
}
