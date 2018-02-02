#ifndef SRC_OPCION_JUGAR_H_
#define SRC_OPCION_JUGAR_H_

#include "Opcion.h"

class Opcion_Jugar : public Opcion{
public:
	Opcion_Jugar();
	~Opcion_Jugar();

	Opcion* update_opcion(double _i_tiempo);
};

#endif /* SRC_OPCION_JUGAR_H_ */