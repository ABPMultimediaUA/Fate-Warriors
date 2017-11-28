#ifndef ARMA_CERCA_H_
#define ARMA_CERCA_H_

#include "Equipable.h"
class Arma_cerca : public Equipable{
public:
	Arma_cerca(float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses);
	virtual ~Arma_cerca();
	void update() override;
	void render() override;
	bool usar() override;
};

#endif /* ARMA_CERCA_H_ */
