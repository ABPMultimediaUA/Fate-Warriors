#include "Lib_Math.h"

unsigned short lib_math_angulo_2_puntos(float _i_x1, float _i_y1, float _i_x2, float i_y2) {
	float _angulo;
	unsigned short _direccion;

	_angulo = atan2(_i_y1 - i_y2, _i_x1 - _i_x2);

	if(_angulo<0) _angulo = _angulo + 2*PI;

	_direccion = _angulo * 180 / PI;

	return _direccion;
}
