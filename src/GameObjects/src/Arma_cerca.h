#ifndef ARMA_CERCA_H_
#define ARMA_CERCA_H_

#include "Arma.h"
class Arma_cerca : public Arma{
public:
	Arma_cerca(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses);
	virtual ~Arma_cerca();
	
	bool usar() override;
	void update() override;
	void render() override;
};

#endif /* ARMA_CERCA_H_ */
