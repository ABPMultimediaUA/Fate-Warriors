#include "Interpolacion_Palanca.h"

Interpolacion_Palanca::Interpolacion_Palanca(Vector3 _i_posicion_inicial, int16_t _rotacion) : Interpolacion( _i_posicion_inicial) {
	_rotacion_anterior = _rotacion;
	_rotacion_actual = _rotacion;

	_cambio_rotacion = false;
}

Interpolacion_Palanca::~Interpolacion_Palanca() {
}


void Interpolacion_Palanca::actualiza_rotacion_palanca(int16_t _i_rotacion_actual) {
	// rotacion_ANTERIOR = rotacion_ACTUAL
	_rotacion_anterior = _rotacion_actual;

	// rotacion_ACTUAL = i_rotacion_actual
	_rotacion_actual = _i_rotacion_actual;

	//std::cout << "Rotacion actual " << (int)_rotacion_actual << "\n";
	//std::cout << "Rotacion anterior " << (int)_rotacion_anterior << "\n";

	// En caso de ser una variacion de mas de 180º, pega una vuelta entera para girar de la forma mas eficiente
	int16_t _diferencia = _rotacion_actual - _rotacion_anterior;
	if(_diferencia > 180) {
		_rotacion_anterior += 360;
		//std::cout << "Rotacion anterior modificada " << (int)_rotacion_anterior << "\n\n";
	}
	else if(_diferencia < -180) {
		_rotacion_anterior -= 360;
		//std::cout << "Rotacion anterior modificada " << (int)_rotacion_anterior << "\n\n";
	}

	_cambio_rotacion = true;
}


int16_t Interpolacion_Palanca::interpola_rotacion_palanca(float _i_interpolacion){
    int16_t _rotacion_interpolada = _rotacion_anterior * (1 -_i_interpolacion) + _rotacion_actual * _i_interpolacion;
    return _rotacion_interpolada;
}