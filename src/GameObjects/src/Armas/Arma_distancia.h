#ifndef ARMA_DISTANCIA_H_
#define ARMA_DISTANCIA_H_

#include "Arma.h"
#include <list>

class Bala;
class Arma_distancia : public Arma{
public:
	Arma_distancia(short _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango);
	virtual ~Arma_distancia();
	void render() override;
	void update(); 
	bool usar(float _i_x, float _i_y, float _i_z) override;

protected: 
		//short Velocidad_bala;


};

#endif /* ARMA_DISTANCIA_H_ */
