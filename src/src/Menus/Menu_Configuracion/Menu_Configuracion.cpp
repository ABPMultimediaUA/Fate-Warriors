#include "Menu_Configuracion.h"

#include "Opcion_Musica.h"
#include "Opcion_SFX.h"
#include "Opcion_Voz.h"

#include "../../Input/Input.h"

#include <iostream>

// Crea las 3 opciones del menu principal
// Musica 	-> Cambia el volumen de la musica
// SFX 		-> Cambia el volumen de los SFX
// Voz 		-> Cambia el volumen de las voces
// Eje X 	-> Invierte el Eje X
// Eje Y 	-> Invierte el Eje Y
Menu_Configuracion::Menu_Configuracion(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_principal];

	_opciones[0] = new Opcion_Musica(_i_input);		// Opcion Musica
	_opciones[1] = new Opcion_SFX(_i_input); 		// Opción Sound Effects
	_opciones[2] = new Opcion_Voz(_i_input); 		// Opcion Voces
	/*_opciones[1] = new Opcion_Eje_X(_i_input); 		// Opción Eje X
	_opciones[2] = new Opcion_Eje_Y(_i_input); 		// Opcion Eje Y
*/
	_opciones[0]->set_opciones(_opciones[2], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[2]);
	_opciones[2]->set_opciones(_opciones[1], _opciones[0]);
	/*_opciones[3]->set_opciones(_opciones[2], _opciones[4]);
	_opciones[4]->set_opciones(_opciones[3], _opciones[0]);*/

	_opcion_actual = _opciones[0];

	_input = _i_input;
}

Menu_Configuracion::~Menu_Configuracion() {
	for(uint8_t i=0; i<_n_opciones_principal; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Configuracion::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);

	pinta_estado();
}

// Pinta por terminal el estado actual
void Menu_Configuracion::pinta_estado() {
	if(_opcion_actual == _opciones[0])
		std::cout << "Opción Music\n";
	if(_opcion_actual == _opciones[1])
		std::cout << "Opción SFX\n";
	if(_opcion_actual == _opciones[2])
		std::cout << "Opción Voice\n";
	/*if(_opcion_actual == _opciones[3])
		std::cout << "Opción Eje X\n";
	if(_opcion_actual == _opciones[4])
		std::cout << "Opción Eje Y\n";*/
}