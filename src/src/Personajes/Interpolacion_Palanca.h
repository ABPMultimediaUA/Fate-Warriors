#ifndef SRC_INTERPOLACION_PALANCA_H_
#define SRC_INTERPOLACION_PALANCA_H_

#include "Interpolacion.h"

class Interpolacion_Palanca : public Interpolacion {
public:
	Interpolacion_Palanca(Vector3 _i_posicion_inicial, int16_t _rotacion);
	~Interpolacion_Palanca();

	void actualiza_rotacion_palanca(int16_t _i_rotacion_actual);	// Interpola la rotacion de la palanca
	int16_t interpola_rotacion_palanca(float _i_interpolacion);		// Devuelve la rotacion interpolada

	inline int16_t get_rotacion_palanca()			{ return _rotacion_actual;}

private:
	int16_t _rotacion_actual;								// Dirección en el ciclo de update actual (el ultimo realizado)					
	int16_t _rotacion_anterior;							// Dirección en el ciclo de update anterior (el anterior)
};

#endif /* SRC_INTERPOLACION_PALANCA_H_ */
