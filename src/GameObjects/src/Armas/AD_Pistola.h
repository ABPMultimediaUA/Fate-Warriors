#ifndef AD_PISTOLA_H_
#define AD_PISTOLA_H_

#include "Arma_distancia.h"

class AD_Pistola : public Arma_distancia{
public:
	AD_Pistola(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Pistola();
	void render() override;
	void update(); 
	bool usar() override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_PISTOLA_H_ */
