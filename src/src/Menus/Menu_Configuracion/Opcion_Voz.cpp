#include "Opcion_Voz.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_Voz::Opcion_Voz(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_Voz::~Opcion_Voz(){
}

void Opcion_Voz::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_voces(_i_vol);
}