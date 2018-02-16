#ifndef INTERRUPTOR_H_
#define INTERRUPTOR_H_

#include "Objeto.h"

class Puerta_Pincho;
class Time;

class Interruptor : public Objeto{
public:
	Interruptor(short _i_id, float _i_x, float _i_y, float _i_z, Puerta_Pincho* _i_objeto_asociado,
			bool _i_es_generador, bool _i_activado, double _i_temporizador);
	virtual ~Interruptor();

	void set_activado(bool _i_activado);
	void update() override;
	void render() override;


private:
	Puerta_Pincho* _objeto_asociado; // Objeto asociado que activa/desactiva
	bool _es_generador; // si es generador, despues de su primer uso se debe destruir
	bool _activado;
	double _temporizador; // Tiempo hasta poder activar/desactivar
	Time* _reloj;
};

#endif /* INTERRUPTOR_H_ */
