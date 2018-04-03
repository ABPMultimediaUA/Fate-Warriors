#ifndef SRC_OPCION_REINICIAR_H_
#define SRC_OPCION_REINICIAR_H_

#include "Opcion.h"

class Opcion_Reiniciar : public Opcion{
public:
	Opcion_Reiniciar(Input* _i_input);
	~Opcion_Reiniciar();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_inicio_pausa(double _t);
};

#endif /* SRC_OPCION_REINICIAR_H_ */