

#include <string>
#include "Nodo.h"
#include "Pasillo.h"
#include "Grafo.h"
#include <stack>
#include <vector>
#ifndef HEADERS_NIVEL_H_
#define HEADERS_NIVEL_H_

const float metro=39.3701;

class Vertice;
class Grafo;
class NPC;

class Nivel {
public:
	static Nivel* nivel_instancia();
	Nivel(std::string &_i_fichero);
	~Nivel();
	void nivel_crear_pasillo(std::ifstream& _Nivel_txt, std::string& _iteracion);
	void nivel_crear_nodo(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion);
	void nivel_crear_objetos(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo);
	void nivel_crear_grafo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion, Grafo* _i_grafo);
	void nivel_crear_arista(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);
	void nivel_crear_adyacentes(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);
	void Update();
	
	
	inline void nivel_inserta_NPC(NPC* _i_npc){
		_lod2->grafo_inserta_NPC( _i_npc);
	}
	inline void nivel_set_lod(int _i_id){
		_lod2->grafo_set_lod(_i_id);
	}
	inline Vertice *nivel_get_vertice(int _i_id){
		return _lod2->grafo_get_vertice(_i_id);
	}
	inline Nodo* nivel_get_nodo(int _i_id){
		return static_cast<Nodo*>(_lod2->grafo_get_vertice(_i_id));
	}
	inline Pasillo * nivel_get_pasillo(int _i_id){
		return static_cast<Pasillo*>(_lod2->grafo_get_vertice(_i_id));
	}
	inline int nivel_get_id_vertice(float _i_x, float _i_y){
		return _lod2->grafo_get_id_vertice(_i_x, _i_y);
	}
	inline std::stack<Vertice*> nivel_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino){
		return _lod2->grafo_camino_corto_l2(_i_origen, _i_destino);
	}
	inline Nodo_blackboard* nivel_get_blackboard(float _i_x, float _i_y){
		return _lod2->grafo_get_blackboard(_i_x, _i_y);
	}
	inline unsigned short nivel_pathfindinglod1(float _i_xorigen, float _i_yorigen, float xdestino, float ydestino){
		return _lod2->grafo_pathfindinglod1(_i_xorigen,_i_yorigen,xdestino,ydestino);
	}
	inline unsigned short nivel_get_lod(int _i_id){
		return _lod2->grafo_get_vertice(_i_id)->_blackboard->get_lod();
	}
private:
	static Nivel* instancia;
	Grafo *_lod2;
	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso);

};
#endif /* HEADERS_NIVEL_H_ */
