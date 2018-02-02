#include "Opcion.h"

Opcion::Opcion() : _opcion_anterior(nullptr), _opcion_siguiente(nullptr) {
}

Opcion::~Opcion() {
}


Opcion* update(double _i_tiempo, Opcion* _this) {
	Opcion* _aux;

	//_aux = comprueba_cambio_opcion();

	if(_aux != _this) {
		return update_opcion();
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