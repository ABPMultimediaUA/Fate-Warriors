#ifndef ARMA_DISTANCIA_H_
#define ARMA_DISTANCIA_H_

#include "Arma.h"
#include <list>

class Bala;
class Arma_distancia : public Arma{
public:
	Arma_distancia(uint16_t _id, float _i_x, float _i_y, float _i_z, Enum_Nombre_Arma _i_tipo, uint8_t _i_uses, uint8_t _i_frecuencia, uint8_t _i_rango,uint8_t _i_danyo );
	virtual ~Arma_distancia();
	void render() override; 
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;


};

#endif /* ARMA_DISTANCIA_H_ */
