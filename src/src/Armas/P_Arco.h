#ifndef P_Arco_H_
#define P_Arco_H_

#include "Proyectil.h"
class P_Arco : public Proyectil{
public:
	P_Arco(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter);
	virtual ~P_Arco();

	void 	Update() override;
	void 	Render() override;

};

#endif /* P_Arco_H_ */
