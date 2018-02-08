#ifndef SRC_Consumible_Vida_Infinita_H_
#define SRC_Consumible_Vida_Infinita_H_

#include "Consumible_Power_Up.h"
#include "../Personajes/Character.h"
class Character;
class Time;


class Consumible_Vida_Infinita : public Consumible_Power_Up{
public:
	Consumible_Vida_Infinita(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Vida_Infinita();

	bool usar(Character* _personaje) override;
	void render() override;
	void activar_tiempo();
	bool comprobar_tiempo_power_up();

};

#endif /* SRC_Consumible_Vida_Infinita_H_ */
