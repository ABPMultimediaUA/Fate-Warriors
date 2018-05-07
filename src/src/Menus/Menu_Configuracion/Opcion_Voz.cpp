#include "Opcion_Voz.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_Voz::Opcion_Voz(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_Voz::~Opcion_Voz(){
}

void Opcion_Voz::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_voces(_i_vol);
}

void Opcion_Voz::actualiza_valores() {
	_volumen = _motor_sonido->get_volumen_voces();
}

void Opcion_Voz::guarda_volumen() {
	_motor_sonido->guarda_volumen_voces(_volumen);

	_sonido->Play_voces_sin_random(6);
}