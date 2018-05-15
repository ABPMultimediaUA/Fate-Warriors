#ifndef SRC_OPCION_VOLUMEN_H_
#define SRC_OPCION_VOLUMEN_H_

#include "../../Opcion.h"

class Interfaz_sonido;

class Opcion_Volumen : public Opcion{
public:
	Opcion_Volumen(Input* _i_input);
	virtual ~Opcion_Volumen();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

protected:
	virtual void set_volumen(float _i_vol) = 0;		// Funcion virtual pura de cambiar el volumen propio que cada hijo implementa
	virtual void guarda_volumen() = 0;				// Funcion virtual que guarda el volumen en la interfaz de sonido

	uint8_t _volumen;								// De 0 a 9
	Interfaz_sonido *_motor_sonido;					// Motor de Sonido
};

#endif /* SRC_OPCION_VOLUMEN_H_ */