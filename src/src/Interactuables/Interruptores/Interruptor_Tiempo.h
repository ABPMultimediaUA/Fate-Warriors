#ifndef INTERRUPTOR_TIEMPO_H_
#define INTERRUPTOR_TIEMPO_H_

#include "../Interruptor.h"

class Interruptor_Tiempo : public Interruptor{
public:
	Interruptor_Tiempo(short _i_id, float _i_x, float _i_z, float _i_rotacion, uint16_t _t_duracion);
	virtual ~Interruptor_Tiempo();

	void accionar();	// Acciona el interruptor y le cambia el estado (si es posible)

	void update() override;		// Comprueba si ha terminado el tiempo y apaga

private:
	uint32_t _duracion;
	uint64_t _t_final_activacion;

	void cambiar_estado_puertas();
};

#endif /* INTERRUPTOR_TIEMPO_H_ */



/*

// TIEMPO
Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion, double _tiempo_duracion);
private: 
	uint16_t _t_inicio;

*/