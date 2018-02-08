#ifndef AD_KATANA_H_
#define AD_KATANA_H_

#include "Arma_cerca.h"

class AC_Katana : public Arma_cerca{
public:
	AC_Katana(uint16_t _id, float _i_x, float _i_y, float _i_z);
	virtual ~AC_Katana();
	void update() override;

	void render() override;
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_KATANA_H_ */
