#ifndef ARISTA_H
#define ARISTA_H

class Vertice;
class Arista
{
	public:

	  Arista *_sig;
	  Vertice *_ady;
	  int _id;
	  int _peso;
	  Arista();
	  virtual ~Arista();
};



#endif