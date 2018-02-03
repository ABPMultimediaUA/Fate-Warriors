#include "Menu_Principal.h"

#include "Opcion_Jugar.h"

#include "../Input.h"

Menu_Principal::Menu_Principal(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones];

	_opciones[0] = new Opcion_Jugar(_i_input);
	_opciones[1] = new Opcion_Jugar(_i_input);
	_opciones[2] = new Opcion_Jugar(_i_input);

	_opcion_actual = _opciones[0];
}

Menu_Principal::~Menu_Principal() {
	for(uint8_t i=0; i<_n_opciones; i++)
		delete _opciones[i];

	delete [] _opciones;
}

void Menu_Principal::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);
}