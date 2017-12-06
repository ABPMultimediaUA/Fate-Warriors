#ifndef AD_Ametralladora_H_
#define AD_Ametralladora_H_

#include "Arma_distancia.h"

class AD_Ametralladora : public Arma_distancia{
public:
	AD_Ametralladora(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Ametralladora();

	void render() override;
	bool usar(float _i_x, float _i_y, float _i_z) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Ametralladora_H_ */
