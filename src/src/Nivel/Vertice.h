#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Arista;
class Vertice
{
	public:

	  Vertice *_sig;
	  Arista *_ady;
	  int _id;

	  Vertice(int _i_id);
	  virtual ~Vertice();
};

#endif