#ifndef SRC_ALLY_H_
#define SRC_ALLY_H_

#include "../NPC.h"

class Ally : public NPC {
public:
	Ally(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	
	virtual ~Ally();
};

#endif /* SRC_ALLY_H_ */
