#ifndef SRC_CONSUMIBLE_AGUA_H_
#define SRC_CONSUMIBLE_AGUA_H_

#include "Consumible.h"
class Interfaz_sonido;

class Consumible_Agua : public Consumible{
public:
	Consumible_Agua(short _id, float _i_x, float _i_y, float _i_z);
	~Consumible_Agua();

	bool usar(Character* _personaje) override;
	Interfaz_sonido* _sonido;
};

#endif /* SRC_CONSUMIBLE_AGUA_H_ */
