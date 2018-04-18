#include "Lib_Math.h"

unsigned short lib_math_angulo_2_puntos(float _i_x1, float _i_y1, float _i_x2, float _i_y2) {
	float _angulo;
	unsigned short _direccion;

	_angulo = atan2(_i_y2 - _i_y1, _i_x2 - _i_x1);

	if(_angulo<0) _angulo = _angulo + 2*PIs;

	_direccion = _angulo * 180 / PIs;

	return _direccion;
}


float lib_math_distancia_2_puntos(float _i_x1, float _i_y1, float _i_x2, float _i_y2) {
	float _d_x = _i_x2 - _i_x1;
	float _d_y = _i_y2 - _i_y1;

	float _distancia_total = sqrt(_d_x*_d_x + _d_y*_d_y);

	return _distancia_total;
}

bool colision_caja(float _i_anx1, float _i_any1, float _i_alx1, float _i_aly1, float _i_x2, float _i_y2){
	if((_i_x2>_i_anx1 && _i_x2<_i_anx1) && (_i_y2>_i_alx1 && _i_y2<_i_aly1) ){
		return true;
	}
	return false;
}