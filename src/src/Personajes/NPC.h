#ifndef SRC_NPC_H_
#define SRC_NPC_H_

#include "Character.h"


class NPC : public Character {
public:
	NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad);
	virtual ~NPC();
  	void update() override;
  	void render() override;
	void move(unsigned long _i_direccion);

private:
};

#endif /* SRC_NPC_H_ */
