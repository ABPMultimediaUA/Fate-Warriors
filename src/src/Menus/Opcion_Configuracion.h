#ifndef SRC_OPCION_CONFIGURACION_H_
#define SRC_OPCION_CONFIGURACION_H_

#include "Opcion.h"

class Opcion_Configuracion : public Opcion{
public:
	Opcion_Configuracion(Input* _i_input);
	~Opcion_Configuracion();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);
};

#endif /* SRC_OPCION_CONFIGURACION_H_ */