#ifndef AD_Bazooka_H_
#define AD_Bazooka_H_

#include "Arma_distancia.h"

class AD_Bazooka : public Arma_distancia{
public:
	AD_Bazooka(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Bazooka();
	void render() override;
	bool usar(float _i_x, float _i_y, float _i_z) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Bazooka_H_ */
