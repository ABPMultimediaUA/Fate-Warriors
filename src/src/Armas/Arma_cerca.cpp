#include "Arma_cerca.h"

Arma_cerca::Arma_cerca(uint16_t _id, float _i_x, float _i_y, float _i_z,Enum_Nombre_Arma _i_tipo, uint8_t _i_uses , uint8_t _i_frecuencia, uint8_t _i_rango,uint8_t _i_danyo ) 
							: Arma(_id, _i_x, _i_y, _i_z, _i_tipo, _i_uses, _i_frecuencia, _i_rango, _i_danyo){
}

Arma_cerca::~Arma_cerca(){

}

Character* Arma_cerca::usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion){
	return 0;
}