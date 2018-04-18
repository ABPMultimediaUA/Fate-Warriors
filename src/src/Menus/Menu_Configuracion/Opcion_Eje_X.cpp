#include "Opcion_Eje_X.h"

#include "../../Input/Input.h"

Opcion_Eje_X::Opcion_Eje_X(Input* _i_input) : Opcion_Eje(_i_input) {
}

Opcion_Eje_X::~Opcion_Eje_X(){

}

void Opcion_Eje_X::invierte() {
	_input->invierte_eje_x();
	actualiza_valores();
}

void Opcion_Eje_X::actualiza_valores() {
	_invertido = _input->get_inversion_eje_x();
}