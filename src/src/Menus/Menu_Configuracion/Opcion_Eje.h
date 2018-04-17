#ifndef SRC_OPCION_EJE_H_
#define SRC_OPCION_EJE_H_

#include "../Opcion.h"

class Opcion_Eje : public Opcion{
public:
	Opcion_Eje(Input* _i_input);
	virtual ~Opcion_Eje();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

protected:
	bool _invertido;

	virtual void invierte() = 0;
};

#endif /* SRC_OPCION_EJE_H_ */