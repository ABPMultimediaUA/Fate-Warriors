#include "Opcion_Volumen.h"

#include "../../../Input/Input.h"
#include "../../../Tiempo/Time.h"

#include "../../../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

Opcion_Volumen::Opcion_Volumen(Input* _i_input) : Opcion(_i_input) {
	_volumen = 5;
    _motor_sonido = Interfaz_sonido::GetInstancia();
}

Opcion_Volumen::~Opcion_Volumen(){
}


// Update de la opción de sonido
Opcion* Opcion_Volumen::update_opcion(double _i_tiempo, Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(std::get<0>(_dir) == true)

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 90 || _direccion == 270) {
			_tiempo_cambio = _t;

			if(_direccion == 90 && _volumen < 9)
				_volumen++;
			else if(_direccion == 270 &&_volumen > 0)
				_volumen--;

			float _vol = _volumen / 9.0;
			set_volumen(_vol);
			guarda_volumen();

			std::cout << "Volumen " << (int)_volumen << "\n";
		}
	}

	return _this;
}