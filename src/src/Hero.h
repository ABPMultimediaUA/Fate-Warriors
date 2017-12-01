#ifndef HERO_H_
#define HERO_H_

#include "Input.h"
#include "sfml/Graphics.hpp"

class Hero {
public:
	Hero();
	virtual ~Hero();
	std::vector<Input_key> update();
	void update_extern(Input_key a);
	void setPosition(float x, float y);
	float position_X();
	float position_Y();
	sf::RectangleShape* get_player();

private:
	sf::RectangleShape* player;
};

#endif /* HERO_H_ */
