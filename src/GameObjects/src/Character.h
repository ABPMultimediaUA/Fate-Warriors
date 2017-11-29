#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "Objeto.h"

class Character : public Objeto{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_vida);
	virtual ~Character();
	void update();
	void render();
	bool usar();

	short get_vida();

protected:
	short _vida;

};

#endif /* SRC_CHARACTER_H_ */
