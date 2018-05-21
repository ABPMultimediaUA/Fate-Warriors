#include "Opcion_VSync.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"
#include "../../../Interfaz/Motor.h"

#include <iostream>

Opcion_VSync::Opcion_VSync(Input* _i_input) : Opcion(_i_input) {
	_vsync = false;
}

Opcion_VSync::~Opcion_VSync(){
}


// Update de la opción de sonido
Opcion* Opcion_VSync::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;

			if(_direccion == 90 && _vsync == false){
				_sonido->Play_menu(3);
				set_vsync();
			}
			else if(_direccion == 270 &&_vsync == true){
				_sonido->Play_menu(1);
				unset_vsync();
			}
		}
	}

	if(_vsync == true) 
		std::cout << "V-Sync ON\n";
	else
		std::cout << "V-Sync OFF\n";

	return _this;
}

void Opcion_VSync::set_vsync() {
	_vsync = true;
	Motor::Motor_GetInstance()->toggleVSync();
}

void Opcion_VSync::unset_vsync() {
	_vsync = false;
	Motor::Motor_GetInstance()->toggleVSync();
}