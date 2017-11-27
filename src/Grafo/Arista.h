#ifndef ARISTA_H
#define ARISTA_H

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