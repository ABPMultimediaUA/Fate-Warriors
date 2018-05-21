#ifndef SRC_CONSUMIBLE_MANAGER_H_
#define SRC_CONSUMIBLE_MANAGER_H_

#include <vector>
#include <cstdint>
#include "../Utilidades/Vector.h"


class Consumible;
class Consumible_Carne;
class Consumible_Patata;
class Time;

class Consumible_Manager{
public:
	Consumible_Manager();
	~Consumible_Manager();

	std::vector<Consumible*>* get_consumibles();
	void borrar_consumible(short id);
	void anyadir_consumible(Vector2 posicion);
	
private:

	std::vector<Consumible*> _consumibles;
	std::vector<Consumible*> _consumibles_a_reusar;

};

#endif /* SRC_CONSUMIBLE_MANAGER_H_ */
