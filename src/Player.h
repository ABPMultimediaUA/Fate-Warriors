#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Character.h"

class Player : public Character{
public:
	Player(float _i_vida, float _i_x, float _i_y);
	virtual ~Player();
};

#endif /* SRC_PLAYER_H_ */
