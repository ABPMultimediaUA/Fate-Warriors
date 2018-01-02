#ifndef VERTICE_H
#define VERTICE_H

class Arista;
class Grafo;
class Nodo_blackboard;
class Vertice
{
	public:
	  
	  //unsigned short _lod;

	  Vertice(float _i_posx, float _i_posy, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1);
	  virtual ~Vertice();
	  Grafo * get_lod1();
	  inline Nodo_blackboard* get_blackboard(){
		  return _blackboard;
	  }
	  inline Vertice * get_sig(){
	  	  return _sig;
	  }
	  inline Arista * get_ady(){
	  	  return _ady;
	  }
	  inline Grafo * get_lod1(){
	  	  return _lod1;
	  }
	  inline int get_id(){
	  	  return id;
	  }
	  inline float get_ancho(){
	  	  return _ancho;
	  }
	  inline float get_alto(){
	  	  return _alto;
	  }
	  inline float get_peso(){
		  return _peso;
	  }
	  inline int get_id_arista(){
	  	  return _id_arista;
	  }
	  float get_coord_x();
	  float get_coord_y();
	  void set_lod(unsigned short cont);
	  void pathfinding(float _i_distancia, Arista* _i_arista_aux, int _i_destino);
	  
	  bool pos2id(float _i_x, float _i_y);
	 private:

	  Nodo_blackboard* _blackboard;
	  Vertice *_sig;
	  Arista *_ady;
	  Grafo *_lod1;
	  int _id;
	  float _posx;
	  float _posy;
	  float _ancho;
	  float _alto;
	  float _peso;
	  int _id_arista;


};

#endif