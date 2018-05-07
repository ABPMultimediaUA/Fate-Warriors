#include "Opcion_Salir_Juego.h"

#include "../Game.h"

#include "../Motor_sonido/Interfaz_sonido.h"

Opcion_Salir_Juego::Opcion_Salir_Juego(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Salir_Juego::~Opcion_Salir_Juego(){

}


// Apaga el motor y sale del juego
Opcion* Opcion_Salir_Juego::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar()) {
		_sonido->Play_menu(0);
		Motor::Motor_GetInstance()->apagar();
	}

	return _this;
}