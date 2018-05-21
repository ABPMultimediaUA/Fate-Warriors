#include "Opcion_Resolucion.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"
#include "../../../Interfaz/Motor.h"

#include <iostream>

Opcion_Resolucion::Opcion_Resolucion(Input* _i_input) : Opcion(_i_input) {
	_resolucion = 1;
}

Opcion_Resolucion::~Opcion_Resolucion(){
}


// Update de la opción de sonido
Opcion* Opcion_Resolucion::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;
			_sonido->Play_menu(2);

			if(_direccion == 90){
				if(_resolucion == 3) {
					_resolucion = 0;
				}
				else {
				_resolucion++;
				}
			}
			else if(_direccion == 270) {
				if(_resolucion == 0) {
					_resolucion = 3;
				}
				else {
				_resolucion--;
				}
			}

			set_resolucion();

			std::cout << "Resolucion " << (int)_resolucion << "\n";
		}
	}

	return _this;
}

void Opcion_Resolucion::set_resolucion() {
	switch(_resolucion) {
		case 0:
			Motor::Motor_GetInstance()->resize_window(640, 480);
			Motor::Motor_GetInstance()->setResolution(0);
		break;

		case 1:
			Motor::Motor_GetInstance()->resize_window(1024, 768);
			Motor::Motor_GetInstance()->setResolution(1);
		break;

		case 2:
			Motor::Motor_GetInstance()->resize_window(1280, 720);
			Motor::Motor_GetInstance()->setResolution(2);
		break;

		case 3:
			Motor::Motor_GetInstance()->resize_window(1920, 1080);
			Motor::Motor_GetInstance()->setResolution(3);
		break;
	}
}


void Opcion_Resolucion::actualiza_valores() {
	_resolucion = Motor::Motor_GetInstance()->get_resolution();
}