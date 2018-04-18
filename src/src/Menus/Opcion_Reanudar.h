#ifndef SRC_OPCION_REANUDAR_H_
#define SRC_OPCION_REANUDAR_H_

#include "Opcion.h"

class Opcion_Reanudar : public Opcion{
public:
	Opcion_Reanudar(Input* _i_input);
	~Opcion_Reanudar();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_inicio_pausa(double _t);
};

#endif /* SRC_OPCION_REANUDAR_H_ */