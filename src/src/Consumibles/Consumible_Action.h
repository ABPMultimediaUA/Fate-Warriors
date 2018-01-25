#ifndef SRC_CONSUMIBLE_ACTION_H_
#define SRC_CONSUMIBLE_ACTION_H_

#include <vector>

class Consumible;
class Consumible_Carne;
class Consumible_Patata;
class Consumible_Manager;
class Consumible_Fuerza;
class NPC_Manager;
class Player;

class Consumible_Action{
public:
	Consumible_Action();
	virtual ~Consumible_Action();
	void comprobar_consumibles();
	void borrar_power_up(Consumible_Fuerza* _i_power_up);

private:

	Player * _player;
	std::vector<Consumible*>* _consumibles;
	Consumible_Manager* _consumibles_manager;
NPC_Manager * _npc_manager;

	
};

#endif /* SRC_CONSUMIBLE_ACTION_H_ */
