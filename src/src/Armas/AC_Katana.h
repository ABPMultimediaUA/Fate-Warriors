#ifndef AD_KATANA_H_
#define AD_KATANA_H_

#include "Arma_cerca.h"

class AC_Katana : public Arma_cerca{
public:
	AC_Katana(uint16_t _id, float _i_x, float _i_y, float _i_z);
	~AC_Katana();
	
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) override;
};

#endif /* AD_KATANA_H_ */
