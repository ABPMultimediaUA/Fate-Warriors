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
	  float _id;
	  float _posx;
	  float _posy;

	  Vertice(int _i_id,float _i_posx, float _i_posy, Grafo *_i_grafo_lod1);
	  Grafo * get_lod1();
	  float get_coord_x();
	  float get_coord_y();
	  virtual ~Vertice();
};

#endif