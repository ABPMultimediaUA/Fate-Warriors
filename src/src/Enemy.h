#ifndef ENEMY_H_
#define ENEMY_H_

#include "sfml/Graphics.hpp"

class Enemy {
public:
	Enemy(short _i_enemy);
	virtual ~Enemy();
	void update();
	void lose_life();
	void setPosition(float x, float y);
	float position_X();
	float position_Y();
	sf::RectangleShape* get_player();

private:
	short id_enemy;
	bool derecha;
	sf::RectangleShape* malote;
};

#endif /* ENEMY_H_ */
