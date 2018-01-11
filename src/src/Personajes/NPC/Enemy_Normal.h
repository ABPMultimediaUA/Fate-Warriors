#ifndef SRC_ENEMY_NORMAL_H_
#define SRC_ENEMY_NORMAL_H_

#include "../NPC.h"

class Enemy_Normal : public NPC {
public:
	Enemy_Normal(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);

	void danyar(short _danyo) override;

	void gestion_ataque() override; // Solucion temporal, hay que estructurar mejor las variantes de ataque
	
	virtual ~Enemy_Normal();
};

#endif /* SRC_ENEMY_NORMAL_H_ */
