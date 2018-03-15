#ifndef SRC_OPCION_JUGAR_ONLINE_H_
#define SRC_OPCION_JUGAR_ONLINE_H_

#include "Opcion.h"

class Opcion_Jugar_Online : public Opcion{
public:
	Opcion_Jugar_Online(Input* _i_input);
	~Opcion_Jugar_Online();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);
};

#endif /* SRC_OPCION_JUGAR_ONLINE_H_ */