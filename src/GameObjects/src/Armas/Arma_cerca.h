#ifndef ARMA_CERCA_H_
#define ARMA_CERCA_H_

#include "Arma.h"
class Arma_cerca : public Arma{
public:
	Arma_cerca(short _id, float _i_x, float _i_y, float _i_z, short tipo, short _i_uses, short _i_frecuencia, short _i_rango);
	virtual ~Arma_cerca();
	
	bool usar(float x, float y, float z) override;
	void update() override;
	void render() override;
};

#endif /* ARMA_CERCA_H_ */
