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
	  unsigned short _lod;
	  unsigned short _n_enemigos;

	  Vertice(float _i_posx, float _i_posy, int _i_id, Grafo *_i_grafo_lod1);
	  Grafo * get_lod1();
	  float get_coord_x();
	  float get_coord_y();
	  void set_lod(unsigned short cont);
	  virtual ~Vertice();
};

#endif