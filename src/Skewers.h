#ifndef SKEWERS_H_
#define SKEWERS_H_

#include "Interactuable.h"
class Skewers : public Interactuable{
public:
	Skewers(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	virtual ~Skewers();
	void change_activate_value();
	bool usar() override;

private:
	short _id;
	bool _activated;
};
#endif /* SKEWERS_H_ */
