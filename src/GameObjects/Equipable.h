#ifndef SRC_EQUIPABLE_H_
#define SRC_EQUIPABLE_H_

#include "Objeto.h"

class Equipable : public Objeto{
public:
	Equipable(float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses);
	virtual ~Equipable();

	bool decrease_uses();
	short get_uses();

protected:
	short _uses;
};

#endif /* SRC_EQUIPABLE_H_ */
