#include "Opcion_Musica.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_Musica::Opcion_Musica(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_Musica::~Opcion_Musica(){

}

void Opcion_Musica::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_musica(_i_vol);
}

void Opcion_Musica::actualiza_valores() {
	_volumen = _motor_sonido->get_volumen_musica();
}

void Opcion_Musica::guarda_volumen() {
	_motor_sonido->guarda_volumen_musica(_volumen);
}