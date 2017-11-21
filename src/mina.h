#ifndef MINA_H_
#define MINA_H_

#include "Interactuable.h"
class Mina : public Interactuable{
public:
	Mina(float _i_x, float _i_y, float _i_ancho, float _i_alto);
	virtual ~Mina();
	void change_activate_value();
	bool usar();
	bool explote();

private:
	short _id;
	bool _activated;
	short _time_out;
};

#endif /* MINA_H_ */
