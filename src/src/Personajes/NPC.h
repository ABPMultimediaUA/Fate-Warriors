#ifndef SRC_NPC_H_
#define SRC_NPC_H_

#include "Character.h"

class Blackboard;


class NPC : public Character {
public:
	NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad);
	virtual ~NPC();
  	void update() override;
  	void render() override;
	void move(unsigned long _i_direccion);
	float getX() override;
	float getY() override;
	float getZ() override;
	void set_blackboard(Blackboard* _i_blackboard);
	Blackboard* get_blackboard();

private:
	Blackboard* _blackboard; //Informacion de la memoria almacenada en el Blackboard

};

#endif /* SRC_NPC_H_ */
