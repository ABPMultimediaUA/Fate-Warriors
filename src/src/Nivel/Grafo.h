#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include "Enum_zonas.h"

const float metro=4.9212625;
class Vertice;
class Arista;
class Nodo_blackboard;
class NPC;
class Grafo
{
	
public:


	Grafo();
	~Grafo();

	void Update();
	bool grafo_vacio();
	int grafo_tamano();
	inline Vertice* get_h(){
		return _h;
	}
	inline void set_h(Vertice* _i_h){
		_h=_i_h;
	}
	void set_tipo_zona(uint8_t _id, Enum_zonas _i_zona);
	Enum_zonas get_tipo_zona(uint8_t _id, Enum_zonas _i_tipo);
	NPC** get_array_NPC(uint8_t _id);

//funciones de blackboard
	Nodo_blackboard* grafo_get_blackboard(float _i_x, float _i_y);
	void grafo_get_numero_posiciones_spawn_enemigos(uint16_t &_i_n_posiciones);
	void grafo_get_posiciones_spawn_enemigos( float** _posiciones);	
	void grafo_inserta_NPC(NPC* _i_npc);

//funciones del grafo
	Vertice * grafo_get_vertice(int _i_id);
	Vertice * grafo_get_vertice(float _i_x, float _i_y);
	int grafo_get_id_vertice(float _i_x, float _i_y);
	Arista * grafo_get_arista(int _i_id);
	void grafo_crea_arista(int _i_origen,int _i_destino, int _i_id);
	void grafo_inserta_arista_bi(Vertice *_i_origen, Vertice *i_i_destino, int _i_id);	
	void grafo_inserta_vertice(Vertice * _nuevo);
	void grafo_lista_adyacencia();
	void grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino);
	

//pathfinding y lod
	void grafo_set_lod(int _i_id);
	uint16_t grafo_pathfinding(float &_i_xorigen, float &_i_yorigen, float xdestino, float ydestino);

//pathfinding estrategico
	void set_peso_tactico_id(float _i_peso_tactico, int _i_id, float _i_x, float _i_y);
	void set_peso_tactico_x_y(float _i_peso_tactico, float _i_x, float _i_y);
	void abrir_cerrar_pasillo(uint16_t peso, uint16_t _id);
	inline void cerrar_pasillo(uint16_t _id){
abrir_cerrar_pasillo(50000, _id);	
	}
	inline void abrir_pasillo(uint16_t _id){
abrir_cerrar_pasillo(0, _id);
	}

private:
	Vertice *_h;

	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino,  int _i_id);
	void actualiza_NPC();
	void grafo_anular();
	Vertice* grafo_pathfindinglod2(float _i_xorigen, float _i_yorigen, float _i_xdestino, float _i_ydestino, Vertice* vertice_origen, Vertice* vertice_destino);
	unsigned short grafo_pathfindinglod1(float _i_xorigen, float _i_yorigen, float _i_xdestino, float _i_ydestino, Vertice* origen, int destino);
};
#endif