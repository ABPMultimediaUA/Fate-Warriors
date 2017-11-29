#ifndef BALA_H_
#define BALA_H_

#include "Interactuable.h"
class Bala : public Interactuable{
public:
	Bala(short _id, float _i_x, float _i_y, float _i_z,  float _i_ancho, float _i_alto);
	virtual ~Bala();

	void update() override;
	void render() override;
	bool usar() override;

	void set_direction(float _i_x, float _i_y, float _i_z);
	void change_activate_value();

	bool get_state();
	void set_collision();
	bool get_collision();

private:

	bool _activated;
	bool _collision;
	float _directionx;
	float _directiony;
	float _directionz;
};

#endif /* MINA_H_ */
