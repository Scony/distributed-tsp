#include "Graph.h"

using namespace std;

Graph::Graph()
{
  this->n = 0;
  this->x = NULL;
  this->y = NULL;
}

Graph::Graph(string graph)
{
  stringstream ss;
  ss << graph;

  ss >> this->n;
  this->x = new int[this->n];
  this->y = new int[this->n];

  int a, b;
  for(int i = 0; i < this->n; i++)
    {
      ss >> a >> b;
      this->setVertex(i,a,b);
    }
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
  FILE * fp;
  if((fp = fopen(fileName.c_str(),"r")))
    {
      char buffer[255];
      fscanf(fp,"NAME: %s\n",buffer);
      fscanf(fp,"COMMENT: %[^\n]\n",buffer);
      fscanf(fp,"TYPE: %s\n",buffer);
      fscanf(fp,"DIMENSION: %d\n",&this->n);
      fscanf(fp,"%[^\n]\n",buffer);
      fscanf(fp,"%[^\n]\n",buffer);

      this->x = new int[this->n];
      this->y = new int[this->n];

      for(int i = 0; i < this->n; i++)
	{
	  int v, x, y;
	  fscanf(fp,"%d %d %d",&v,&x,&y);
	  this->setVertex(v-1,x,y);
	}
    }
  else
    throw new Exception("Cannot read graph");
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

int Graph::getN()
{
  return this->n;
}

string Graph::toString()
{
  char buff[32];
  sprintf(buff,"%d",this->n);
  string out = string(buff);
  for(int i = 0; i < this->n; i++)
    {
      sprintf(buff," %d %d",this->x[i],this->y[i]);
      out += string(buff);
    }

  return out;
}
