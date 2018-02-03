#ifndef SRC_CONSUMIBLE_FUERZA_H_
#define SRC_CONSUMIBLE_FUERZA_H_

#include "Consumible_Power_Up.h"
#include "../Personajes/Character.h"
class Character;
class Time;


class Consumible_Fuerza : public Consumible_Power_Up{
public:
	Consumible_Fuerza(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Fuerza();

	bool usar(Character* _personaje) override;
	void render() override;
	void activar_tiempo();
	bool comprobar_tiempo_power_up();
};

#endif /* SRC_CONSUMIBLE_FUERZA_H_ */
