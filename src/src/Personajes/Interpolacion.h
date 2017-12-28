#ifndef SRC_INTERPOLACION_H_
#define SRC_INTERPOLACION_H_

#include "../Utilidades/Vector.h"

// La clase interpolacion almacena las posiciones actuales y anteriores de los personajes
// Devuelve posiciones interpoladas entre esas dos posiciones para los ciclos de render
class Interpolacion {
public:
	Interpolacion(Vector3 _i_posicion_inicial);
	virtual ~Interpolacion();


	void actualiza_posicion(Vector3 _i_posicion_actual); 	// Hace la posicion anterior la antigua posicion actual y pone la nueva actual
	Vector3 interpola_posicion(float _i_interpolacion); 	// Devuelve la posicion interpolada para un % de render
	
private:
	Vector3* _posicion_actual;								// Posicion en el ciclo de update actual (el ultimo realizado)
	Vector3* _posicion_anterior;							// Posicion en el ciclo de update anterior (el anterior)

};

#endif /* SRC_INTERPOLACION_H_ */