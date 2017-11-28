#include "Nodo.h"

Nodo::Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id): Vertice(_i_id), _nodo_x(_i_x),
	_nodo_y(_i_y), _nodo_ancho(_i_ancho), _nodo_alto(_i_alto), _estado(1), _id(_i_id){
}

Nodo::~Nodo() {
}
void Nodo::nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id){
	Skewers* _objeto=new Skewers(_i_x, _i_y, _i_ancho, _i_alto, _i_id);
	_objetos.push_back(_objeto);
	delete _objeto;
}


