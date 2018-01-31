#ifndef VERTICE_H
#define VERTICE_H
#include <cstdlib>
#include "Enum_vertices.h"
class Arista;
class Grafo;
class Nodo_blackboard;
class Vertice
{
	public:
	  
	  //unsigned short _lod;

	  Vertice(float _i_posx, float _i_posy, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1);
	  virtual ~Vertice();
	  inline Nodo_blackboard* get_blackboard(){
		  return _blackboard;
	  }
	  inline float get_coord_x(){
		return _posx;
	  }
	  inline float get_coord_y(){
		return _posy;
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
	  	  return _id;
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
	  Enum_vertices get_tipo(){
		return _tipo;
	  }
		inline float get_peso_tactico(){
			return _peso_tactico;
		}
	  inline void set_sig(Vertice* _i_sig){
		  _sig=_i_sig;
	  }
	  inline void set_ady(Arista* _i_ady){
		 _ady=_i_ady;
	  }
	  inline void set_id_arista(int _i_id){
		_id_arista=_i_id;
	  }
	  inline void set_peso(float _i_peso){
		  _peso=_i_peso;
	  }
		inline void set_peso_tactico(float _i_peso){
			_peso_tactico=_i_peso;
		}

	  u_int8_t get_lod();

	  void set_lod(unsigned short cont);
	  void pathfinding(float _i_distancia, Arista* _i_arista_aux, int _i_destino);
	  
	  bool pos2id(float _i_x, float _i_y);
	 protected:
	  Enum_vertices _tipo;
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
	  float _peso_tactico;
	  int _id_arista;


};

#endif