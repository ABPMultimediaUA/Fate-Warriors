#ifndef P_Pistola_H_
#define P_Pistola_H_

#include "Proyectil.h"
class P_Pistola : public Proyectil{
public:
	P_Pistola(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter);
	virtual ~P_Pistola();

	void 	Update() override;
	void 	Render() override;

};

#endif /* P_Pistola_H_ */
