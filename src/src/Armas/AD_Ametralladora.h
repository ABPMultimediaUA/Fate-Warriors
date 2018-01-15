#ifndef AD_Ametralladora_H_
#define AD_Ametralladora_H_

#include "Arma_distancia.h"

class AD_Ametralladora : public Arma_distancia{
public:
	AD_Ametralladora(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Ametralladora();
	void update() override;

	void render() override;
	bool usar(float _i_x, float _i_y, float _i_z) override;

protected: 
		//short Velocidad_bala;
	Objeto_Motor* _objeto;
};

#endif /* AD_Ametralladora_H_ */
