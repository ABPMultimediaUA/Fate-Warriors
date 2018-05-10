#include "Opcion_Eje_X.h"

#include "../../Input/Input.h"
#include "../../Interfaz/Motor.h"

Opcion_Eje_X::Opcion_Eje_X(Input* _i_input) : Opcion_Eje(_i_input) {
	Motor::Motor_GetInstance()->set_eje_x(_invertido);
}

Opcion_Eje_X::~Opcion_Eje_X(){

}

void Opcion_Eje_X::invierte() {
	_input->invierte_eje_x();
	actualiza_valores();
	Motor::Motor_GetInstance()->set_eje_x(_invertido);
}

void Opcion_Eje_X::actualiza_valores() {
	_invertido = _input->get_inversion_eje_x();
}