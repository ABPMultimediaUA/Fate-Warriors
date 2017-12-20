#ifndef VERTICE_H
#define VERTICE_H

class Arista;
class Grafo;
class NPC;
class Nodo_blackboard;
class Vertice
{
	public:
	  Nodo_blackboard* _blackboard;
	  Vertice *_sig;
	  Arista *_ady;
	  Grafo *_lod1;
	  float _id;
	  float _posx;
	  float _posy;
	  float _ancho;
	  float _alto;
	  float _peso;
	  int _id_arista;
	  unsigned short _lod;

	  Vertice(float _i_posx, float _i_posy, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1);
	  Grafo * get_lod1();
	  inline Nodo_blackboard* get_blackboard(){
		  return _blackboard;
	  }
	  float get_coord_x();
	  float get_coord_y();
	  void set_lod(unsigned short cont);
	  void pathfinding(float _i_distancia, Arista* _i_arista_aux, int _i_destino);
	  virtual ~Vertice();
	  bool pos2id(float _i_x, float _i_y);

};

#endif