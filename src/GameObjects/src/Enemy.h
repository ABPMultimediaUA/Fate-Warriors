#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Character.h"

class Enemy : public Character{
public:
	Enemy(short _id, float _i_x, float _i_y, float _i_z, short _i_vida);
	virtual ~Enemy();
	bool usar() override;
	void update() override;
	void render() override;
	short get_vida();

protected:
	short _vida;

};

#endif /* SRC_ENEMY_H_ */
