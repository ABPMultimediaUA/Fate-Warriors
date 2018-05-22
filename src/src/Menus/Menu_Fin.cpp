#include "Menu_Fin.h"

#include "Opcion_Reiniciar.h"
#include "Opcion_Salir_Partida.h"

#include "../Game.h"

#include "../Input/Input.h"

#include "../Tiempo/Time.h"

#include <iostream>

// Crea las 2 opciones del menu de fin de partida
// Reiniciar -> Al darle a OK se reinicia la partida
// Salir Partida -> Se sale al menu principal
Menu_Fin::Menu_Fin(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_fin];


	_opciones[0] = new Opcion_Reiniciar(_i_input);	// Opcion Reanudar
	_opciones[1] = new Opcion_Salir_Partida(_i_input); 	// Opcion Salir de Partida

	_opciones[0]->set_opciones(_opciones[1], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[0]);

	_opcion_actual = _opciones[0];

	_input = _i_input;
}

Menu_Fin::~Menu_Fin() {
	for(uint8_t i=0; i<_n_opciones_fin; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Fin::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);

	//pinta_estado();
}


void Menu_Fin::set_tiempo_fin() {
	Time *_reloj = Time::Instance();
	_reloj->pausar_reloj();
	_opciones[0]->set_tiempo(_reloj->get_current_sin_pausas());
	_opcion_actual = _opciones[0];
}


// Pinta por terminal el estado actual
void Menu_Fin::pinta_estado() {
	std::cout << "Menu Fin Partida\n";
	if(_opcion_actual == _opciones[0])
		std::cout << "Opción Reiniciar\n";
	if(_opcion_actual == _opciones[1])
		std::cout << "Opción Salir Partida\n";
}

uint8_t Menu_Fin::get_i_opcion() { 
  	for(uint8_t i=0; i<_n_opciones_fin; i++) { 
    	if(_opcion_actual == _opciones[i]) 
      		return i; 
  	} 
  	return 0;
}