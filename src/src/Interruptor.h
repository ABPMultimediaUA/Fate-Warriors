#ifndef INTERRUPTOR_H_
#define INTERRUPTOR_H_

#include "Objeto.h"

class Interruptor : public Objeto{
public:
	Interruptor(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_objeto_asociado,
			bool _i_es_generador, bool _i_activado, short _i_temporizador);
	virtual ~Interruptor();

	void set_activado(bool _i_activado);

private:
	short _id_objeto_asociado; // Objeto asociado que activa/desactiva
	bool _es_generador; // si es generador, despues de su primer uso se debe destruir
	bool _activado;
	short _temporizador; // Tiempo hasta poder activar/desactivar
};

#endif /* INTERRUPTOR_H_ */
