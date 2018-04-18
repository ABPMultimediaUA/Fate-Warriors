


#include <string>
#include "Nodo.h"
#include "Pasillo.h"
#include "Grafo.h"
#include <stack>
#include <vector>
#ifndef HEADERS_NIVEL_H_
#define HEADERS_NIVEL_H_


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
	
	inline void nivel_set_peso_tactico_id(float _i_peso_tactico,int _i_id, float _i_x, float _i_y){
		_lod2->set_peso_tactico_id(_i_peso_tactico,_i_id, _i_x, _i_y);
	}
	inline void nivel_set_peso_tactico_x_y(float _i_peso_tactico, float _i_x, float _i_y){
		_lod2->set_peso_tactico_x_y(_i_peso_tactico,_i_x,_i_y);
	}
	inline void nivel_cerrar_pasillo(uint16_t _id){
		_lod2->cerrar_pasillo(_id);
	}
	inline void nivel_abrir_pasillo(uint16_t _id){
		_lod2->abrir_pasillo(_id);
	}
	inline void nivel_inserta_NPC(NPC* _i_npc){
		_lod2->grafo_inserta_NPC( _i_npc);
	}
	inline void nivel_set_lod(int _i_id){
		_lod2->grafo_set_lod(_i_id);
	}
	inline void nivel_get_numero_posiciones_spawn(uint16_t &_i_n_posiciones){
		_lod2->grafo_get_numero_posiciones_spawn_enemigos(_i_n_posiciones);
	}
	inline void nivel_get_posiciones_spawn( float** _posiciones){
		_lod2->grafo_get_posiciones_spawn_enemigos( _posiciones);
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
	inline Nodo_blackboard* nivel_get_blackboard(float _i_x, float _i_y){
		return _lod2->grafo_get_blackboard(_i_x, _i_y);
	}
	inline NPC** nivel_get_array_NPC(int _i_id){
		return _lod2->get_array_NPC(_i_id);
	}
	inline uint16_t nivel_pathfinding(float &_i_xorigen, float &_i_yorigen, float xdestino, float ydestino){
		return _lod2->grafo_pathfinding( _i_xorigen, _i_yorigen, xdestino, ydestino);
	}
	inline unsigned short nivel_get_lod(int _i_id){
		return _lod2->grafo_get_vertice(_i_id)->get_blackboard()->get_lod();
	}
	inline void nivel_set_tipo_zona(uint8_t _id, Enum_zonas _i_zona){
		_lod2->set_tipo_zona(_id, _i_zona);
	}
	inline Enum_zonas nivel_get_tipo_zona(uint8_t _id, Enum_zonas _i_tipo){
		return _lod2->get_tipo_zona(_id, _i_tipo);
	}

private:
	static Nivel* instancia;
	Grafo *_lod2;
	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso);

};
#endif /* HEADERS_NIVEL_H_ */
