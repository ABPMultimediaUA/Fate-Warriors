#include "Nodo.h"

Nodo::Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo, int _i_zona): 
Vertice( _i_x, _i_y, _i_ancho, _i_alto, _i_id, _i_grafo){
	
	_blackboard = new Nodo_blackboard(_i_zona);
}

Nodo::~Nodo() {
	delete _blackboard;
}
void Nodo::nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id){
	//Skewers* _objeto=new Skewers(_i_x, _i_y, _i_ancho, _i_alto, _i_id);
//	_objetos.push_back(_objeto);
//	delete _objeto;
}


