#ifndef ARISTA_H
#define ARISTA_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>

class Vertice;
class Arista
{
	public:

	  Arista *sig;
	  Vertice *ady;
	  int id;
	  int peso;
	  Arista();
	  virtual ~Arista();
};



#endif