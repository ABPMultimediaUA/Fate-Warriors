#ifndef SRC_LIB_MATH_H_
#define SRC_LIB_MATH_H_

#include <cstdint>
#include <math.h>
#include <tgmath.h>

//PI para hacer operaciones de senos y cosenos
const double PIs = std::acos(-1);

unsigned short lib_math_angulo_2_puntos(float _i_x1, float _i_y1, float _i_x2, float i_y2);

float lib_math_distancia_2_puntos(float _i_x1, float _i_y1, float _i_x2, float i_y2);

template <typename T>
inline int8_t lib_math_sgn(T v) {
    return (v > T(0)) - (v < T(0));
}

#endif /* SRC_LIB_MATH_H_ */
