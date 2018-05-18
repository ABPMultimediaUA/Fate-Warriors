#include "Nodo.h"
#include <iostream>

Nodo::Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo, int _i_zona, uint8_t _i_n_npc): 
Vertice( _i_x, _i_y, _i_ancho, _i_alto, _i_id, _i_grafo){
	_blackboard = new Nodo_blackboard(_i_zona,_i_n_npc);
	_tipo_vertice=Vertice_Nodo;
}

Nodo::~Nodo() {
	delete _blackboard;

}
void Nodo::nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id){
}


