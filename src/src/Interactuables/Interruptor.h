#ifndef INTERRUPTOR_H_
#define INTERRUPTOR_H_

#include "../Objeto.h"

#include <vector>

class Puerta_Pincho;
class Time;

class Interruptor : public Objeto{
public:
	Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion);
	virtual ~Interruptor();

	virtual void iniciar_interruptor();					// Inicia el cambio de objetivo de camara del interruptor
	virtual void accionar() = 0;				// Acciona el interruptor y le cambia el estado (si es posible)
	virtual void accionar_sin_propagar();		// Acciona el interruptor sin propagar

	void agregar_puerta(Puerta_Pincho* _puerta);					// Agrega una puerta a sus asociadas
	virtual void agregar_interruptor(Interruptor* _interruptor);	// Solo para la propagadora

	virtual void update();

	Puerta_Pincho* get_puerta_asociada();

protected:
	Time* _reloj;
	std::vector<Puerta_Pincho*> _puertas_asociadas;		// Vector con todas las puertas asociadas
	bool _estado;										// Estado del interruptor (false = no activado / true = activado)

private:
	Objeto_Motor* _palito;								// Modelado del Palo del interruptor (hay que animarlo)
};

#endif /* INTERRUPTOR_H_ */



/*

// BASE
Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion);
private: 
	bool _estado;
	Puerta_Pincho** _puertas;

*/