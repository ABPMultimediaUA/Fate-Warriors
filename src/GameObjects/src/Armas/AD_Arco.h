#ifndef AD_Arco_H_
#define AD_Arco_H_

#include "Arma_distancia.h"

class AD_Arco : public Arma_distancia{
public:
	AD_Arco(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Arco();
	void render() override;
	void update(); 
	bool usar(float _i_x, float _i_y, float _i_z) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Arco_H_ */
