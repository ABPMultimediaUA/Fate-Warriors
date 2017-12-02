#ifndef PROYECTIL_H_
#define PROYECTIL_H_

#include "../Interactuable.h"
class Proyectil : public Interactuable{
public:
	Proyectil(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Proyectil();

  virtual void Update() = 0;
	virtual void Render() = 0;
	void set_direction(float _i_x, float _i_y, float _i_z);
	void change_activate_value();

	bool get_state();
	void set_has_impacted();
	bool get_has_impacted();

private:

	bool _impacted;
	float _directionx;
	float _directiony;
	float _directionz;
};

#endif /* MINA_H_ */
