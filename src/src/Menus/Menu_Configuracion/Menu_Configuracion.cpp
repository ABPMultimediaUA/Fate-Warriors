#include "Menu_Configuracion.h"

#include "Opcion_Musica.h"
#include "Opcion_SFX.h"
#include "Opcion_Voz.h"
#include "Opcion_Sonido_Menu.h"
#include "Opcion_Eje_X.h"
#include "Opcion_Eje_Y.h"

#include "../../Input/Input.h"

#include <iostream>

// Crea las 6 opciones del menu de configuracion
// Musica 		-> Cambia el volumen de la musica
// SFX 			-> Cambia el volumen de los SFX
// Voz 	   		-> Cambia el volumen de las voces
// Sonido Menu 	-> Cambia el volumen del sonido del menu
// Eje X 		-> Invierte el Eje X
// Eje Y 		-> Invierte el Eje Y
Menu_Configuracion::Menu_Configuracion(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_configuracion];

	_opciones[0] = new Opcion_Musica(_i_input);			// Opcion Musica
	_opciones[1] = new Opcion_SFX(_i_input); 			// Opción Sound Effects
	_opciones[2] = new Opcion_Voz(_i_input); 			// Opcion Voces
	_opciones[3] = new Opcion_Sonido_Menu(_i_input); 	// Opcion Sonido Menu
	_opciones[4] = new Opcion_Eje_X(_i_input); 			// Opción Eje X
	_opciones[5] = new Opcion_Eje_Y(_i_input); 			// Opcion Eje Y

	_opciones[0]->set_opciones(_opciones[5], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[2]);
	_opciones[2]->set_opciones(_opciones[1], _opciones[3]);
	_opciones[3]->set_opciones(_opciones[2], _opciones[4]);
	_opciones[4]->set_opciones(_opciones[3], _opciones[5]);
	_opciones[5]->set_opciones(_opciones[4], _opciones[0]);

	_opcion_actual = _opciones[0];

	_input = _i_input;
}

Menu_Configuracion::~Menu_Configuracion() {
	for(uint8_t i=0; i<_n_opciones_configuracion; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Configuracion::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);

	pinta_estado();
}


void Menu_Configuracion::actualiza() {
	for(uint8_t i=0; i<_n_opciones_configuracion; i++) {
		_opciones[i]->actualiza_valores();
	}
	
	_opcion_actual = _opciones[0];
}


// Pinta por terminal el estado actual
void Menu_Configuracion::pinta_estado() {
	if(_opcion_actual == _opciones[0])
		std::cout << "Opción Music\n";
	else if(_opcion_actual == _opciones[1])
		std::cout << "Opción SFX\n";
	else if(_opcion_actual == _opciones[2])
		std::cout << "Opción Voice\n";
	else if(_opcion_actual == _opciones[3])
		std::cout << "Opción Sonido Menu\n";
	else if(_opcion_actual == _opciones[4])
		std::cout << "Opción Eje X\n";
	else if(_opcion_actual == _opciones[5])
		std::cout << "Opción Eje Y\n";
}

uint8_t Menu_Configuracion::get_i_configuracion() { 
	for(uint8_t i=0; i<_n_opciones_configuracion; i++) { 
    	if(_opcion_actual == _opciones[i]) 
    		return i; 
  	} 
}