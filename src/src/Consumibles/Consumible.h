#ifndef SRC_CONSUMIBLE_H_
#define SRC_CONSUMIBLE_H_

#include "../Objeto.h"

class Character;
class Time;

class Consumible : public Objeto{
public:
	Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor);
	virtual ~Consumible();
	
	bool comprobar_colision(Character* _character);
	virtual bool usar(Character* modificar) = 0;
	short get_valor();
	void set_tiempo_espera();

protected:
	bool ha_pasado_tiempo_suficiente();
	short _valor;
	Time* _reloj;
	double tiempo_espera;
};

#endif /* SRC_CONSUMIBLE_H_ */