#include "Menu_Configuracion.h"

#include "Opcion_Cambio_Submenu.h"

#include "Submenu_1/Opcion_Musica.h"
#include "Submenu_1/Opcion_SFX.h"
#include "Submenu_1/Opcion_Voz.h"
#include "Submenu_1/Opcion_Sonido_Menu.h"

#include "Submenu_2/Opcion_Eje_X.h"
#include "Submenu_2/Opcion_Eje_Y.h"

#include "Submenu_3/Opcion_Resolucion.h"
#include "Submenu_3/Opcion_VSync.h"
#include "Submenu_3/Opcion_Fullscreen.h"
#include "Submenu_3/Opcion_Texturas.h"

#include "../../Input/Input.h"
#include "../../Interfaz/Motor.h"

#include <iostream>

// Crea las 13 opciones del menu de configuracion
// Cambio Submenu 1	->	Cambia a los submenenus anterior (3) y siguiente (2)
// Musica 		-> Cambia el volumen de la musica
// SFX 			-> Cambia el volumen de los SFX
// Voz 	   		-> Cambia el volumen de las voces
// Sonido Menu 	-> Cambia el volumen del sonido del menu

// Cambio Submenu 2	->	Cambia a los submenenus anterior (1) y siguiente (3)
// Eje X 		-> Invierte el Eje X
// Eje Y 		-> Invierte el Eje Y

// Cambio Submenu 3	->	Cambia a los submenenus anterior (2) y siguiente (1)
// Resolucion 	-> Cambia la resolucion entre las disponibles
// V-SYNC 		-> Activa y desactiva el V-Sync
// Fullscreen 	-> Activa y desactiva el Fullscreen
// Texturas 	-> Cambia el tamaño de textuas entre las disponibles

Menu_Configuracion::Menu_Configuracion(Input* _i_input) {
	_opciones = new Opcion*[_n_opciones_configuracion];

	// ---------- SUBMENU 1 ---------- //
	_opciones[0] = new Opcion_Cambio_Submenu(_i_input);	// Opcion Cambio Submenu 1
	_opciones[1] = new Opcion_Musica(_i_input);			// Opcion Musica
	_opciones[2] = new Opcion_SFX(_i_input); 			// Opción Sound Effects
	_opciones[3] = new Opcion_Voz(_i_input); 			// Opcion Voces
	_opciones[4] = new Opcion_Sonido_Menu(_i_input); 	// Opcion Sonido Menu

	_opciones[0]->set_opciones(_opciones[4], _opciones[1]);
	_opciones[1]->set_opciones(_opciones[0], _opciones[2]);
	_opciones[2]->set_opciones(_opciones[1], _opciones[3]);
	_opciones[3]->set_opciones(_opciones[2], _opciones[4]);
	_opciones[4]->set_opciones(_opciones[3], _opciones[0]);


	// ---------- SUBMENU 2 ---------- //
	_opciones[5] = new Opcion_Cambio_Submenu(_i_input);	// Opcion Cambio Submenu 2
	_opciones[6] = new Opcion_Eje_X(_i_input); 			// Opción Eje X
	_opciones[7] = new Opcion_Eje_Y(_i_input); 			// Opcion Eje Y

	_opciones[5]->set_opciones(_opciones[7], _opciones[6]);
	_opciones[6]->set_opciones(_opciones[5], _opciones[7]);
	_opciones[7]->set_opciones(_opciones[6], _opciones[5]);


	// ---------- SUBMENU 3 ---------- //
	_opciones[8] = new Opcion_Cambio_Submenu(_i_input);	// Opcion Cambio Submenu 3
	_opciones[9] = new Opcion_Resolucion(_i_input);		// Opcion Resolucion
	_opciones[10] = new Opcion_VSync(_i_input);			// Opcion V-Sync
	_opciones[11] = new Opcion_Fullscreen(_i_input);	// Opcion Fullscreen
	_opciones[12] = new Opcion_Texturas(_i_input);		// Opcion Texturas

	_opciones[8]->set_opciones(_opciones[12], _opciones[9]);
	_opciones[9]->set_opciones(_opciones[8], _opciones[10]);
	_opciones[10]->set_opciones(_opciones[9], _opciones[11]);
	_opciones[11]->set_opciones(_opciones[10], _opciones[12]);
	_opciones[12]->set_opciones(_opciones[11], _opciones[8]);


	_opcion_actual = _opciones[0];

	_input = _i_input;


	_opciones[0]->agrega_submenus(_opciones[8], _opciones[5]);
	_opciones[5]->agrega_submenus(_opciones[0], _opciones[8]);
	_opciones[8]->agrega_submenus(_opciones[5], _opciones[0]);
}

Menu_Configuracion::~Menu_Configuracion() {
	for(uint8_t i=0; i<_n_opciones_configuracion; i++)
		delete _opciones[i];

	delete [] _opciones;
}

// Se hace el update de la opción actual
void Menu_Configuracion::update(double _i_tiempo) {
	_opcion_actual = _opcion_actual->update(_i_tiempo, _opcion_actual);
	Motor::Motor_GetInstance()->actualizaMenuConfig(get_i_configuracion());
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
		std::cout << "Opcion Cambio Submenu 1\n";
	else if(_opcion_actual == _opciones[1])
		std::cout << "Opción Music\n";
	else if(_opcion_actual == _opciones[2])
		std::cout << "Opción SFX\n";
	else if(_opcion_actual == _opciones[3])
		std::cout << "Opción Voice\n";
	else if(_opcion_actual == _opciones[4])
		std::cout << "Opción Sonido Menu\n";

	else if(_opcion_actual == _opciones[5])
		std::cout << "Opcion Cambio Submenu 2\n";
	else if(_opcion_actual == _opciones[6])
		std::cout << "Opción Eje X\n";
	else if(_opcion_actual == _opciones[7])
		std::cout << "Opción Eje Y\n";

	else if(_opcion_actual == _opciones[8])
		std::cout << "Opcion Cambio Submenu 3\n";
	else if(_opcion_actual == _opciones[9])
		std::cout << "Opcion Resolucion\n";
	else if(_opcion_actual == _opciones[10])
		std::cout << "Opcion V-Sync\n";
	else if(_opcion_actual == _opciones[11])
		std::cout << "Opcion Fullscreen\n";
	else if(_opcion_actual == _opciones[12])
		std::cout << "Opcion Texturas\n";
}

uint8_t Menu_Configuracion::get_i_configuracion() { 
	for(uint8_t i=0; i<_n_opciones_configuracion; i++) { 
    	if(_opcion_actual == _opciones[i]) 
    		return i; 
  	} 
  	return 0;
}

uint8_t Menu_Configuracion::get_i_submenu() {
	uint8_t _submenu_actual;
	uint8_t _n_opcion = get_i_configuracion();
	
	if(_n_opcion < 5)
		_submenu_actual = 0;
	else if(_n_opcion < 8)
		_submenu_actual = 1;
	else
		_submenu_actual = 2;

	return _submenu_actual;
}