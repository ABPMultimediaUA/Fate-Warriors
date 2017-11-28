#ifndef SRC_CONSUMIBLE_H_
#define SRC_CONSUMIBLE_H_

#include "Objeto.h"

class Consumible : public Objeto{
public:
	Consumible(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	virtual ~Consumible();

};

#endif /* SRC_CONSUMIBLE_H_ */
