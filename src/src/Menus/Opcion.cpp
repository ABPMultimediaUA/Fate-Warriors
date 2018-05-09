#include "Opcion.h"

#include "../Game.h"
#include "../Tiempo/Time.h"

#include "../Motor_sonido/Interfaz_sonido.h"

// En principio el momento de cambio es 0
uint32_t Opcion::_tiempo_cambio = 0;

Opcion::Opcion(Input* _i_input) : _opcion_anterior(nullptr), _opcion_siguiente(nullptr) {
	_input = _i_input;
	 _sonido= Interfaz_sonido::GetInstancia();
}

Opcion::~Opcion() {
}

// Comprueba si se ha pulsado para mover entre menus, si no es así hace el update propio
// Devuelve la opción a la que se debe cambiar
Opcion* Opcion::update(double _i_tiempo, Opcion* _this) {
	Opcion* _aux;

	_aux = comprueba_cambio_opcion(_this);

	if(_aux == _this) {
		return update_opcion(_i_tiempo, _this);
	}
	
	return _aux;
}

// Comprueba si ha pasado el tiempo y si se ha pulsado para cambiar
Opcion* Opcion::comprueba_cambio_opcion(Opcion* _this) {
	auto _dir = _input->get_direccion();

	uint32_t _t = Time::Instance()->get_current_sin_pausas();

	if(_t > (_tiempo_cambio+200) && std::get<0>(_dir) == true) {
		uint16_t _direccion = std::get<1>(_dir);

		if(_direccion == 0 || _direccion == 180) {
			_tiempo_cambio = _t;
			//sonido
			_sonido->Play_menu(2);
			if(_direccion == 0){				
				return _opcion_anterior;
			}
			else{
				return _opcion_siguiente;
			}
		}
	}

	// Si no se cumple se devuelve a si mismo
	return _this;
}


void Opcion::set_opciones(Opcion* _i_opcion_anterior, Opcion* _i_opcion_siguiente) {
	if(_i_opcion_anterior != nullptr)
		set_opcion_anterior(_i_opcion_anterior);

	if(_i_opcion_siguiente != nullptr)
		set_opcion_siguiente(_i_opcion_siguiente);
}

void Opcion::set_opcion_anterior(Opcion* _i_opcion) {
	_opcion_anterior = _i_opcion;
}

void Opcion::set_opcion_siguiente(Opcion* _i_opcion) {
	_opcion_siguiente = _i_opcion;
}

void Opcion::set_tiempo(double _t) {
	_tiempo_cambio = _t;
}

bool Opcion::get_dentro() {
	return false;
}

uint8_t Opcion::get_i_configuracion() {
	return 0;
}

void Opcion::actualiza_valores() {
}