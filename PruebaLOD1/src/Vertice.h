#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Arista;
class Grafo;
class Vertice
{
	public:

	  Vertice *_sig;
	  Arista *_ady;
	  Grafo *_lod1;
	  int _id;
	  int _posx;
	  int _posy;

	  Vertice();
	  Grafo * get_lod1();
	  int get_coord_x();
	  int get_coord_y();
	  virtual ~Vertice();
};



#endif