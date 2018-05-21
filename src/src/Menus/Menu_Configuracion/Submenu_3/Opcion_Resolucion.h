#ifndef SRC_OPCION_RESOLUCION_H_
#define SRC_OPCION_RESOLUCION_H_

#include "../../Opcion.h"

class Interfaz_sonido;

class Opcion_Resolucion : public Opcion{
public:
	Opcion_Resolucion(Input* _i_input);
	virtual ~Opcion_Resolucion();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_resolucion();

private:
	uint8_t _resolucion;								// De 0 a 3
};

#endif /* SRC_OPCION_RESOLUCION_H_ */