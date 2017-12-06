#ifndef TRIGGER_REGION_H_
#define TRIGGER_REGION_H_

#include "../Utilidades/Vector.h"

class Trigger_region {
public:
	virtual ~Trigger_region(){}
	virtual bool esta_tocando(Vector2 Posicion_Personaje, double Radio)const = 0;
	
};

#endif /* TRIGGER_REGION_H_ */