#ifndef SRC_CONSUMIBLE_CARNE_H_
#define SRC_CONSUMIBLE_CARNE_H_

#include "Consumible.h"
class Interfaz_sonido;

class Consumible_Carne : public Consumible{
public:
	Consumible_Carne(short _id, float _i_x, float _i_y, float _i_z);
	~Consumible_Carne();

	bool usar(Character* _personaje) override;
	Interfaz_sonido* _sonido;
};

#endif /* SRC_CONSUMIBLE_CARNE_H_ */
