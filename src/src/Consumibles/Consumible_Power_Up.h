#ifndef SRC_Consumible_Power_Up_H_
#define SRC_Consumible_Power_Up_H_

#include "Consumible.h"
#include "../Personajes/Character.h"
class Character;
class Time;


class Consumible_Power_Up : public Consumible{
public:
	Consumible_Power_Up(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Power_Up();

	bool usar(Character* _personaje) override;
	void render() override;
	void activar_tiempo();
	bool comprobar_tiempo_power_up();
protected:
	Character* _personaje;
	Time* _reloj;
	double _duracion_power_up;
};

#endif /* SRC_Consumible_Power_Up_H_ */
