#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "Objeto.h"

class Character : public Objeto{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida);
	virtual ~Character();
	void update();
	void render();

	short get_vida();

protected:
	short _vida;

};

#endif /* SRC_CHARACTER_H_ */
