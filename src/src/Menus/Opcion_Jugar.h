#ifndef SRC_OPCION_JUGAR_H_
#define SRC_OPCION_JUGAR_H_

#include "Opcion.h"

class Opcion_Jugar : public Opcion{
public:
	Opcion_Jugar(Input* _i_input);
	~Opcion_Jugar();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);
};

#endif /* SRC_OPCION_JUGAR_H_ */