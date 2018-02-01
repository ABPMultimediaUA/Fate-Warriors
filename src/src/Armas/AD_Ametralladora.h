#ifndef AD_Ametralladora_H_
#define AD_Ametralladora_H_

#include "Arma_distancia.h"

class AD_Ametralladora : public Arma_distancia{
public:
	AD_Ametralladora(uint16_t _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Ametralladora();
	void update() override;

	void render() override;
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Ametralladora_H_ */
