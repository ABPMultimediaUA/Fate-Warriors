#ifndef SRC_ALLY_H_
#define SRC_ALLY_H_

#include "../NPC.h"

class Ally : public NPC {
public:
	Ally(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	virtual ~Ally();
	
	void danyar(short _danyo) override;

};

#endif /* SRC_ALLY_H_ */
