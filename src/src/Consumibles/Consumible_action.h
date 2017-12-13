#ifndef SRC_Consumible_action_H_
#define SRC_Consumible_action_H_

#include <vector>

class Consumible;
class Consumible_carne;
class Consumible_patata;
class Consumible_manager;
class Player;

class Consumible_action{
public:
	Consumible_action();
	virtual ~Consumible_action();
	void comprobar_consumibles();

private:

	Player * _player;
	std::vector<Consumible*> _consumibles;
	Consumible_manager* _consumibles_manager;
	
};

#endif /* SRC_Consumible_action_H_ */
