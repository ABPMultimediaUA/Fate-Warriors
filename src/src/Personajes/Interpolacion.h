#ifndef SRC_INTERPOLACION_H_
#define SRC_INTERPOLACION_H_

#include <cstdint>

#include "../Utilidades/Vector.h"

// La clase interpolacion almacena las posiciones actuales y anteriores de los personajes
// Devuelve posiciones interpoladas entre esas dos posiciones para los ciclos de render
class Interpolacion {
public:
	Interpolacion(Vector3 _i_posicion_inicial);
	virtual ~Interpolacion();


	void actualiza_posicion(Vector3 _i_posicion_actual); 	// Hace la posicion anterior la antigua posicion actual y pone la nueva actual
	Vector3 interpola_posicion(float _i_interpolacion); 	// Devuelve la posicion interpolada para un % de render

	void actualiza_direccion(int16_t _i_direccion_actual); // Hace la direccion anterior la antigua direccion actual y pone la nueva actual
	int16_t interpola_direccion(float _i_interpolacion); 	// Devuelve la direccion interpolada para un % de render

	inline Vector3* get_posicion_actual() {	return _posicion_actual;}

	inline void cambio_direccion(bool _i_cambio) { _cambio_direccion = _i_cambio;}

	inline int16_t get_direccion_actual() { return _direccion_actual; }

	inline bool get_cambio_direccion() { return _cambio_direccion; }

private:
	Vector3* _posicion_actual;								// Posicion en el ciclo de update actual (el ultimo realizado)
	Vector3* _posicion_anterior;							// Posicion en el ciclo de update anterior (el anterior)

	int16_t _direccion_actual;								// Dirección en el ciclo de update actual (el ultimo realizado)					
	int16_t _direccion_anterior;							// Dirección en el ciclo de update anterior (el anterior)

	bool _cambio_direccion;									// Indica si se ha producido un cambio de direccion en el ciclo de update actual
};

#endif /* SRC_INTERPOLACION_H_ */