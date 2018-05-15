#ifndef SRC_OPCION_EJE_Y_H_
#define SRC_OPCION_EJE_Y_H_

#include "Opcion_Eje.h"

class Opcion_Eje_Y : public Opcion_Eje{
public:
	Opcion_Eje_Y(Input* _i_input);
	~Opcion_Eje_Y();
	
	void actualiza_valores();

protected:
	void invierte();
};

#endif /* SRC_OPCION_EJE_Y_H_ */