#include "Opcion_Resolucion.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"

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

			if(_direccion == 90 && _resolucion < 3){
				_resolucion++;
			}
			else if(_direccion == 270 &&_resolucion > 0){
				_resolucion--;
			}

			set_resolucion();

			std::cout << "Resolucion " << (int)_resolucion << "\n";
		}
	}

	return _this;
}

void Opcion_Resolucion::set_resolucion() {
	// Haz lo que tengas que hacer con OPENGL
}