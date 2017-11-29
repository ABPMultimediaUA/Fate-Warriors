#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"

class Enemy : Character{
public:
	Enemy(short id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_vida);
	virtual ~Enemy();


private:

};

#endif /* ENEMY_H_ */
