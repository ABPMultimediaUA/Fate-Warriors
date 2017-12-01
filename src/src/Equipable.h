#ifndef SRC_EQUIPABLE_H_
#define SRC_EQUIPABLE_H_

#include "Objeto.h"

class Equipable : public Objeto{
public:
	Equipable(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	virtual ~Equipable();

};

#endif /* SRC_EQUIPABLE_H_ */
