#ifndef AD_Bazooka_H_
#define AD_Bazooka_H_

#include "Arma_distancia.h"

class AD_Bazooka : public Arma_distancia{
public:
	AD_Bazooka(uint16_t _id, float _i_x, float _i_y, float _i_z);
	~AD_Bazooka();
	void render() override;
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_Bazooka_H_ */
