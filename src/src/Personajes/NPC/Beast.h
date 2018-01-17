#ifndef SRC_BEAST_H_
#define SRC_BEAST_H_

#include "Enemy.h"

class Beast : public Enemy {
public:
	Beast(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	
	virtual ~Beast();

	void danyar(short _danyo) override;

	void gestion_ataque() override; // Solucion temporal, hay que estructurar mejor las variantes de ataque
};

#endif /* SRC_BEAST_H_ */
