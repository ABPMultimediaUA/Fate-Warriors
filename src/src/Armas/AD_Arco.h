#ifndef AD_Arco_H_
#define AD_Arco_H_

#include "Arma_distancia.h"

class AD_Arco : public Arma_distancia{
public:
	AD_Arco(uint16_t _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Arco();
	void render() override;
	Character* usar(uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Arco_H_ */
