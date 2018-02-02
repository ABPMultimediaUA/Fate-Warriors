#include "Menu_Principal.h"

#include "Opcion.h"

Menu_Principal::Menu_Principal() {
	_opciones = new Opcion*[_n_opciones];

	_opcion_actual = _opciones[0];
}

Menu_Principal::~Menu_Principal() {
	for(uint8_t i=0; i<_n_opciones; i++)
		delete _opciones[i];

	delete [] _opciones;
}

void Menu_Principal::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo);
}