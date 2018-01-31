#ifndef P_AMETRALLADORA_H_
#define P_AMETRALLADORA_H_

#include "Proyectil.h"
class P_Ametralladora : public Proyectil{
public:
	P_Ametralladora(uint16_t _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter);
	virtual ~P_Ametralladora();

	void 	Update() override;
	void 	Render() override;

};

#endif /* P_AMETRALLADORA_H_ */
