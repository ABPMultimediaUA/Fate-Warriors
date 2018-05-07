#include "Menu_Principal.h"

#include "Opcion_Jugar.h"
#include "Opcion_Configuracion.h"
#include "Opcion_Salir_Juego.h"

#include "../Input/Input.h"

#include "../Interfaz/Motor.h"

// Crea las 3 opciones del menu principal
// Jugar -> Al darle a OK empieza la partida
// Configuracion -> Con sus opciones
// Salir -> Se sale del juego
Menu_Principal::Menu_Principal(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_principal];

	_opciones[0] = new Opcion_Jugar(_i_input);	// Opcion Jugar
	_opciones[1] = new Opcion_Configuracion(_i_input); 	// Opción Configuración
	_opciones[2] = new Opcion_Salir_Juego(_i_input); 	// Opcion Salir

	_opciones[0]->set_opciones(_opciones[2], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[2]);
	_opciones[2]->set_opciones(_opciones[1], _opciones[0]);

	_opcion_actual = _opciones[0];

	_input = _i_input;
}

Menu_Principal::~Menu_Principal() {
	for(uint8_t i=0; i<_n_opciones_principal; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Principal::update(double _i_tiempo) {

	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);

	pinta_estado();
}

uint8_t Menu_Principal::get_i_opcion() { 
  for(uint8_t i=0; i<_n_opciones_principal; i++) { 
    if(_opcion_actual == _opciones[i]) 
      return i; 
  } 
}

// Pinta por terminal el estado actual
void Menu_Principal::pinta_estado() {
	if(_opcion_actual == _opciones[0])
		std::cout << "Opción Jugar\n";
	if(_opcion_actual == _opciones[1])
		std::cout << "Opción Configuración\n";
	if(_opcion_actual == _opciones[2])
		std::cout << "Opción Salir\n";
}