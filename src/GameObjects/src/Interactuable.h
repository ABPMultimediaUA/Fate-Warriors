#ifndef SRC_INTERACTUABLE_H_
#define SRC_INTERACTUABLE_H_

#include "Objeto.h"

class Interactuable : public Objeto{
public:
	Interactuable(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Interactuable();

};

#endif /* SRC_INTERACTUABLE_H_ */
