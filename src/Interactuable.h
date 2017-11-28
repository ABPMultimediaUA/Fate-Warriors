#ifndef SRC_INTERACTUABLE_H_
#define SRC_INTERACTUABLE_H_

#include "Objeto.h"

class Interactuable : public Objeto{
public:
	Interactuable(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	virtual ~Interactuable();

};

#endif /* SRC_INTERACTUABLE_H_ */
