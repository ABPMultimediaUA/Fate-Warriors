#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Arista;
class Vertice
{
	public:

	  Vertice *sig;
	  Arista *ady;
	  int id;

	  Vertice();
	  virtual ~Vertice();
};



#endif