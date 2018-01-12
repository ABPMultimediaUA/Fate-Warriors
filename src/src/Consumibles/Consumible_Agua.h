#ifndef SRC_CONSUMIBLE_AGUA_H_
#define SRC_CONSUMIBLE_AGUA_H_

#include "Consumible.h"

class Consumible_Agua : public Consumible{
public:
	Consumible_Agua(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Agua();

	bool usar(Character* _personaje) override;
	void render() override;

};

#endif /* SRC_CONSUMIBLE_AGUA_H_ */
