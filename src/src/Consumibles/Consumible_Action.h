#ifndef SRC_CONSUMIBLE_ACTION_H_
#define SRC_CONSUMIBLE_ACTION_H_

#include <vector>

class Consumible;
class Consumible_Carne;
class Consumible_Patata;
class Consumible_Manager;
class Player;

class Consumible_Action{
public:
	Consumible_Action();
	virtual ~Consumible_Action();
	void comprobar_consumibles();

private:

	Player * _player;
	std::vector<Consumible*>* _consumibles;
	Consumible_Manager* _consumibles_manager;
	
};

#endif /* SRC_CONSUMIBLE_ACTION_H_ */
