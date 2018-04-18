#include "Opcion_Eje_Y.h"

#include "../../Input/Input.h"

Opcion_Eje_Y::Opcion_Eje_Y(Input* _i_input) : Opcion_Eje(_i_input) {
}

Opcion_Eje_Y::~Opcion_Eje_Y(){

}

void Opcion_Eje_Y::invierte() {
	_input->invierte_eje_y();
	actualiza_valores();
}

void Opcion_Eje_Y::actualiza_valores() {
	_invertido = _input->get_inversion_eje_y();
}