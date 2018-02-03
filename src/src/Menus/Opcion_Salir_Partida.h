#ifndef SRC_OPCION_SALIR_PARTIDA_H_
#define SRC_OPCION_SALIR_PARTIDA_H_

#include "Opcion.h"

class Opcion_Salir_Partida : public Opcion{
public:
	Opcion_Salir_Partida(Input* _i_input);
	~Opcion_Salir_Partida();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);
};

#endif /* SRC_OPCION_SALIR_PARTIDA_H_ */