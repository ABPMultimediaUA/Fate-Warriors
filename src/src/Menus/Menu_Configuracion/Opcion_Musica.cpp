#include "Opcion_Musica.h"

#include "../../Motor_sonido/Interfaz_sonido.h"

Opcion_Musica::Opcion_Musica(Input* _i_input) : Opcion_Volumen(_i_input) {
}

Opcion_Musica::~Opcion_Musica(){

}

void Opcion_Musica::set_volumen(float _i_vol) {
	_motor_sonido->set_volumen_musica(_i_vol);
}