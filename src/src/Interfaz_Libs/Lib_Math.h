#ifndef SRC_LIB_MATH_H_
#define SRC_LIB_MATH_H_

#include <tgmath.h>
#include <math.h>

//PI para hacer operaciones de senos y cosenos
const double PI = std::acos(-1);

unsigned short lib_math_angulo_2_puntos(float _i_x1, float _i_y1, float _i_x2, float i_y2);

float lib_math_distancia_2_puntos(float _i_x1, float _i_y1, float _i_x2, float i_y2);

#endif /* SRC_LIB_MATH_H_ */
