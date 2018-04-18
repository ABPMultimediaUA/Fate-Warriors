#ifndef INTERRUPTOR_PROPAGADOR_H_
#define INTERRUPTOR_PROPAGADOR_H_

#include "../Interruptor.h"

class Interruptor_Propagador : public Interruptor{
public:
	Interruptor_Propagador(short _i_id, float _i_x, float _i_z, float _i_rotacion, short _i_rotacion_x, short _i_rotacion_y, short _i_distancia);
	virtual ~Interruptor_Propagador();

	void iniciar_interruptor() override;
	void accionar();				// Acciona el interruptor y le cambia el estado (si es posible) y propaga a sus puertas asociadas
	void accionar_sin_propagar() override;	// Acciona el interruptor y sus puertas, pero no propaga

	void agregar_interruptor(Interruptor* _interruptor) override;

private:
	std::vector<Interruptor*> _interruptores_asociados;		// Vector con todas las puertas asociadas

	void cambiar_estado_puertas();
	void propagar_interruptores();
};

#endif /* INTERRUPTOR_PROPAGADOR_H_ */



/*

// Propagador
Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion);
private: 
	Interruptor** _interruptor_afecta;

*/