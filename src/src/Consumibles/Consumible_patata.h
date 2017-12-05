#ifndef SRC_CONSUMIBLE_PATATA_H_
#define SRC_CONSUMIBLE_PATATA_H_

#include "Consumible.h"

class Consumible_patata : public Consumible{
public:
	Consumible_patata(short _id, float _i_x, float _i_y, float _i_z, short vida);
	virtual ~Consumible_patata();

	bool usar() override;
	void render() override;

};

#endif /* SRC_CONSUMIBLE_PATATA_H_ */
