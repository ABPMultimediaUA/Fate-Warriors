#include "Opcion_Fullscreen.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

Opcion_Fullscreen::Opcion_Fullscreen(Input* _i_input) : Opcion(_i_input) {
	_fullscreen = true;
}

Opcion_Fullscreen::~Opcion_Fullscreen(){
}


// Update de la opción de sonido
Opcion* Opcion_Fullscreen::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;

			if(_direccion == 90 && _fullscreen == false){
				_sonido->Play_menu(3);
				set_fullscreen();
			}
			else if(_direccion == 270 &&_fullscreen == true){
				_sonido->Play_menu(1);
				unset_fullscreen();
			}
		}
	}

	if(_fullscreen == true) 
		std::cout << "Fullscreen ON\n";
	else
		std::cout << "Fullscreen OFF\n";

	return _this;
}

void Opcion_Fullscreen::set_fullscreen() {
	_fullscreen = true;
	// Haz lo que tengas que hacer con OPENGL
}

void Opcion_Fullscreen::unset_fullscreen() {
	_fullscreen = false;
	// Haz lo que tengas que hacer con OPENGL
}