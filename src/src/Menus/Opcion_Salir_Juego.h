#ifndef SRC_OPCION_SALIR_JUEGO_H_
#define SRC_OPCION_SALIR_JUEGO_H_

#include "Opcion.h"

#include "../Interfaz/Motor.h"

class Opcion_Salir_Juego : public Opcion{
public:
	Opcion_Salir_Juego(Input* _i_input);
	~Opcion_Salir_Juego();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);
};

#endif /* SRC_OPCION_SALIR_JUEGO_H_ */