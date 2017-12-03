#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Character.h"
class ckeyboardman;

class Player : public Character{
public:
	Player(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Player();
	void update() override;
	void render() override;
	short get_vida();

	//ckeyboardman* _KeyMan;

};

#endif /* SRC_PLAYER_H_ */
