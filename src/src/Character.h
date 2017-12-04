#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

class Character {
public:
	Character(float _i_vida, float _i_x, float _i_y);
	virtual ~Character();

	float get_x();
	float get_y();

protected:
	float _vida;
	float _x;
	float _y;
};

#endif /* SRC_CHARACTER_H_ */
