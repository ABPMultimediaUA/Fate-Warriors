#include "Opcion_Cambio_Submenu.h"

#include "../../Input/Input.h"
#include "../../Tiempo/Time.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

Opcion_Cambio_Submenu::Opcion_Cambio_Submenu(Input* _i_input) : Opcion(_i_input) {
}

Opcion_Cambio_Submenu::~Opcion_Cambio_Submenu(){
}


// Update de la opción de sonido
Opcion* Opcion_Cambio_Submenu::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90) {
			_sonido->Play_menu(2);
			_tiempo_cambio = _t;
			return _submenu_der;
		} 
		else if(_direccion == 270) {
			_sonido->Play_menu(2);
			_tiempo_cambio = _t;
			return _submenu_izq;
		}
	}

	return _this;
}


void Opcion_Cambio_Submenu::agrega_submenus(Opcion* _i_opcion_izq, Opcion* _i_opcion_der) {
	_submenu_izq = _i_opcion_izq;
	_submenu_der = _i_opcion_der;
}