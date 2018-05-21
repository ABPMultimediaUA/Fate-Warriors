#include "Opcion_Configuracion.h"

#include "../Game.h"
#include "../Tiempo/Time.h"

#include "Menu_Configuracion/Menu_Configuracion.h"

#include "../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

Opcion_Configuracion::Opcion_Configuracion(Input* _i_input) : Opcion(_i_input) {
	_dentro_menu = false;

	_configuracion = new Menu_Configuracion(_input);
}

Opcion_Configuracion::~Opcion_Configuracion(){
	delete _configuracion;
}


// Comprueba si ha pasado el tiempo y si se ha pulsado para cambiar Y SI NO ESTA EN EL MENU DE CONFIG
Opcion* Opcion_Configuracion::comprueba_cambio_opcion(Opcion* _this) {
	if(_dentro_menu == false) {

		auto _dir = _input->get_direccion();

		uint32_t _t = Time::Instance()->get_current_sin_pausas();

		if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
			uint16_t _direccion = std::get<1>(_dir);

			_tiempo_cambio = _t;

			if(_direccion == 0) {
				_sonido->Play_menu(2);
				return _opcion_anterior;
			}
			else if(_direccion == 180) {
				_sonido->Play_menu(2);
				return _opcion_siguiente;
			}
		}
	}	

	// Si no se cumple se devuelve a si mismo
	return _this;
}

Opcion* Opcion_Configuracion::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_dentro_menu == true) {			// Esta en el menu de config
		 if(_input->get_dash()) { 			// Salir del menu
			_sonido->Play_menu(1);
		 	_dentro_menu = false;
		 	std::cout << "Salir de CONFIG\n";
		 }
		 else {
		 	_configuracion->update(_i_tiempo);
		 }
	}
	else if(_input->get_saltar()) {			// Entrar al menu
		_sonido->Play_menu(0);
		_dentro_menu = true;
		_configuracion->actualiza();
		std::cout << "Entrar a CONFIG\n";
	}

	return _this;
}


bool Opcion_Configuracion::get_dentro() {
	return _dentro_menu;
}

uint8_t Opcion_Configuracion::get_i_configuracion() { 
	return _configuracion->get_i_configuracion(); 
}

uint8_t Opcion_Configuracion::get_resolucion() {
	return _configuracion->get_resolucion();
}

uint8_t Opcion_Configuracion::get_texturas() {
	return _configuracion->get_texturas();
}