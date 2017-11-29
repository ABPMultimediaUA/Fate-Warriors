#ifndef SRC_CONSUMIBLE_VIDA_H_
#define SRC_CONSUMIBLE_VIDA_H_

#include "Consumible.h"

class Consumible_vida : public Consumible{
public:
	Consumible_vida(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short vida);
	virtual ~Consumible_vida();

	bool usar() override;
	void update() override;
	void render() override;

};

#endif /* SRC_CONSUMIBLE_VIDA_H_ */
