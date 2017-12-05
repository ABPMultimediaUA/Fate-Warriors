#ifndef P_BAZOOKA_H_
#define P_BAZOOKA_H_

#include "Proyectil.h"
class P_Bazooka : public Proyectil{
public:
	P_Bazooka(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter);
	virtual ~P_Bazooka();

	void 	Update() override;
	void 	Render() override;

};

#endif /* P_BAZOOKA_H_ */
