#ifndef INTERRUPTOR_UN_USO_H_
#define INTERRUPTOR_UN_USO_H_

#include "../Interruptor.h"

class Interruptor_Un_Uso : public Interruptor{
public:
	Interruptor_Un_Uso(short _i_id, float _i_x, float _i_z, float _i_rotacion, short _i_rotacion_x, short _i_rotacion_y, short _i_distancia);
	virtual ~Interruptor_Un_Uso();

	void accionar();	// Acciona el interruptor y le cambia el estado (si es posible)
};

#endif /* INTERRUPTOR_UN_USO_H_ */



/*

// 1 USO
Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion);

*/