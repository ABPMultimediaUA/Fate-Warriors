#include "Opcion_Texturas.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"
#include "../../../Moose_Engine/src/TGestorRecursos.h"
#include "../../../Interfaz/Motor.h"

#include <iostream>

Opcion_Texturas::Opcion_Texturas(Input* _i_input) : Opcion(_i_input) {
	_texturas = 0;
}

Opcion_Texturas::~Opcion_Texturas(){
}


// Update de la opción de sonido
Opcion* Opcion_Texturas::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;
			_sonido->Play_menu(2);

			if(_direccion == 90){
				if(_texturas == 2) {
					_texturas = 0;
				}
				else {
				_texturas++;
				}
			}
			else if(_direccion == 270) {
				if(_texturas == 0) {
					_texturas = 2;
				}
				else {
				_texturas--;
				}
			}

			set_texturas();

			std::cout << "Texturas " << (int)_texturas << "\n";
		}
	}

	return _this;
}

void Opcion_Texturas::set_texturas() {
	//	Opciones de texturas: 
	// 		1 - LOW
	// 		2 - MEDIUM
	// 		3 - HIGH
	TGestorRecursos::get_instancia()->setCalidad(_texturas+1);
	Motor::Motor_GetInstance()->setCalidadTexturas(_texturas);
}

void Opcion_Texturas::actualiza_valores() {
	_texturas = Motor::Motor_GetInstance()->get_calidad_texturas();
}