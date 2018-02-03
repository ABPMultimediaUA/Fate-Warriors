#include "Opcion.h"

#include "../Game.h"
#include <iostream>

Opcion::Opcion(Input* _i_input) : _opcion_anterior(nullptr), _opcion_siguiente(nullptr) {
	_input = _i_input;
}

Opcion::~Opcion() {
}


Opcion* Opcion::update(double _i_tiempo, Opcion* _this) {
	Opcion* _aux;

	//_aux = comprueba_cambio_opcion();

	if(_aux != _this) {
		return update_opcion(_i_tiempo, _this);
	}
	
	return _aux;
}


void Opcion::set_opciones(Opcion* _i_opcion_anterior, Opcion* _i_opcion_siguiente) {
	if(_i_opcion_anterior != nullptr)
		set_opcion_anterior(_i_opcion_anterior);

	if(_i_opcion_siguiente != nullptr)
	set_opcion_siguiente(_i_opcion_siguiente);
}

void Opcion::set_opcion_anterior(Opcion* _i_opcion) {
	_opcion_anterior = _i_opcion;
}

void Opcion::set_opcion_siguiente(Opcion* _i_opcion) {
	_opcion_siguiente = _i_opcion;
}