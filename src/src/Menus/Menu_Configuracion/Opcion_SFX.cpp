#include "Opcion_SFX.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_SFX::Opcion_SFX(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_SFX::~Opcion_SFX(){
}

void Opcion_SFX::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_sfx(_i_vol);
}

void Opcion_SFX::actualiza_valores() {
	_volumen = _motor_sonido->get_volumen_sfx();
}

void Opcion_SFX::guarda_volumen() {
	_motor_sonido->guarda_volumen_sfx(_volumen);

	_sonido->Play_personaje(1);
}