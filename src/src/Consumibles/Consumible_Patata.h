#ifndef SRC_CONSUMIBLE_PATATA_H_
#define SRC_CONSUMIBLE_PATATA_H_

#include "Consumible.h"

class Consumible_Patata : public Consumible{
public:
	Consumible_Patata(short _id, float _i_x, float _i_y, float _i_z);
	~Consumible_Patata();

	bool usar(Character* _personaje) override;
};

#endif /* SRC_CONSUMIBLE_PATATA_H_ */
