#include "Menu_Pausa.h"

#include "Opcion_Reanudar.h"
#include "Opcion_Configuracion.h"
#include "Opcion_Salir_Partida.h"

#include "../Game.h"
#include "../Input.h"

#include "../Tiempo/Time.h"

#include <iostream>

// Crea las 3 opciones del menu de pausa
// Reanudar -> Al darle a OK se reanuda la partida
// Configuracion -> Con sus opciones
// Salir Partida -> Se sale de la partida
Menu_Pausa::Menu_Pausa(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_pausa];


	_opciones[0] = new Opcion_Reanudar(_i_input);	// Opcion Reanudar
	_opciones[1] = new Opcion_Configuracion(_i_input); 	// Opción Configuración
	_opciones[2] = new Opcion_Salir_Partida(_i_input); 	// Opcion Salir de Partida

	_opciones[0]->set_opciones(_opciones[2], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[2]);
	_opciones[2]->set_opciones(_opciones[1], _opciones[0]);

	_opcion_actual = _opciones[0];

	_input = _i_input;
}

Menu_Pausa::~Menu_Pausa() {
	for(uint8_t i=0; i<_n_opciones_pausa; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Pausa::update(double _i_tiempo) {
	//Comprueba si se pulsa para salir de la pausa
    if(_input->get_pausa() && Time::Instance()->get_tiempo_inicio_pausa() > 200){
    	Game::game_instancia()->cambio_a_update_partida();
    }

	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);

	//pinta_estado();
}


void Menu_Pausa::set_tiempo_pausa() {
	Time *_reloj = Time::Instance();
	_reloj->pausar_reloj();
	_opciones[0]->set_tiempo(_reloj->get_current_sin_pausas());
	_opcion_actual = _opciones[0];
}


// Pinta por terminal el estado actual
void Menu_Pausa::pinta_estado() {
	if(_opcion_actual == _opciones[0])
		std::cout << "Opción Reanudar\n";
	if(_opcion_actual == _opciones[1])
		std::cout << "Opción Configuración\n";
	if(_opcion_actual == _opciones[2])
		std::cout << "Opción Salir Partida\n";
}