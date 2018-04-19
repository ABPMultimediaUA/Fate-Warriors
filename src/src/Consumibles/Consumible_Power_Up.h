#ifndef SRC_Consumible_Power_Up_H_
#define SRC_Consumible_Power_Up_H_

#include "Consumible.h"

class Time;

class Consumible_Power_Up : public Consumible{
public:
	Consumible_Power_Up(short _id, float _i_x, float _i_y, float _i_z);
	~Consumible_Power_Up();

	bool usar(Character* _personaje) override;
	void activar_tiempo();
	bool comprobar_tiempo_power_up();
	void cambiar_modelado() override;


protected:
	Character* _personaje;
	Time* _reloj;
	double _duracion_power_up;
};

#endif /* SRC_Consumible_Power_Up_H_ */
