#ifndef SRC_CONSUMIBLE_FUERZA_H_
#define SRC_CONSUMIBLE_FUERZA_H_

#include "Consumible_Power_Up.h"

class Character;

class Consumible_Fuerza : public Consumible_Power_Up{
public:
	Consumible_Fuerza(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Fuerza();

	bool usar(Character* _personaje) override;
	void activar_tiempo();
	bool comprobar_tiempo_power_up();
	void cambiar_modelado() override;

};

#endif /* SRC_CONSUMIBLE_FUERZA_H_ */
