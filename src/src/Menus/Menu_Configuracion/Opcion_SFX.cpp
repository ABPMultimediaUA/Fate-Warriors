#include "Opcion_SFX.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_SFX::Opcion_SFX(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_SFX::~Opcion_SFX(){
}

void Opcion_SFX::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_sfx(_i_vol);
}