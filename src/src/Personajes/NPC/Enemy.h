#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "../NPC.h"

class Enemy : public NPC {
public:
	Enemy(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo _i_tipo_npc);
	
	virtual ~Enemy();
};

#endif /* SRC_ENEMY_H_ */
