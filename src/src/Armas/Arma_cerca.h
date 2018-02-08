#ifndef ARMA_CERCA_H_
#define ARMA_CERCA_H_

#include "Arma.h"
class Arma_cerca : public Arma{
public:

	Arma_cerca(uint16_t _id, float _i_x, float _i_y, float _i_z, Enum_Nombre_Arma tipo, uint8_t _i_uses, uint8_t _i_frecuencia, uint8_t _i_rango,uint8_t _i_danyo );

	virtual ~Arma_cerca();
	
	Character* usar(uint16_t _i_direccion) override;
	void render() override;
};

#endif /* ARMA_CERCA_H_ */
