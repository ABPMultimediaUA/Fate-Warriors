#ifndef ARISTA_H
#define ARISTA_H

class Vertice;
class Arista
{
	public:

	  Arista *_sig;
	  Vertice *_ady;
	  float _peso;
	  int _id;
	  Arista();
	  ~Arista();
};



#endif