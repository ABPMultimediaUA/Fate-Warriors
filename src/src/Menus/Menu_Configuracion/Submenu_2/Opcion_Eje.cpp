#include "Opcion_Eje.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

Opcion_Eje::Opcion_Eje(Input* _i_input) : Opcion(_i_input) {
	_invertido = false;
}

Opcion_Eje::~Opcion_Eje(){
}


// Update de la opción de sonido
Opcion* Opcion_Eje::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;

			if(_direccion == 90 && _invertido == true) {
				_sonido->Play_menu(3);
				invierte();
			}
			else if(_direccion == 270 && _invertido == false) {
				_sonido->Play_menu(1);
				invierte();
			}
		}
	}

	/*if(_invertido == true) 
		std::cout << "ON\n";
	else
		std::cout << "OFF\n";*/

	return _this;
}