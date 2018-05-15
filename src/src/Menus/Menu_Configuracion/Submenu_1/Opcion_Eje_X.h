#ifndef SRC_OPCION_EJE_X_H_
#define SRC_OPCION_EJE_X_H_

#include "Opcion_Eje.h"

class Opcion_Eje_X : public Opcion_Eje{
public:
	Opcion_Eje_X(Input* _i_input);
	~Opcion_Eje_X();
	
	void actualiza_valores();

protected:
	void invierte();
};

#endif /* SRC_OPCION_EJE_X_H_ */