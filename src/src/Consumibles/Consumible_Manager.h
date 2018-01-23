#ifndef SRC_CONSUMIBLE_MANAGER_H_
#define SRC_CONSUMIBLE_MANAGER_H_

#include <vector>

class Consumible;
class Consumible_Carne;
class Consumible_Patata;
class Consumible_Fuerza;


class Consumible_Manager{
public:
	Consumible_Manager();
	virtual ~Consumible_Manager();

	std::vector<Consumible*>* get_consumibles();
	std::vector<Consumible_Patata*> get_consumibles_patata();
	std::vector<Consumible_Carne*> get_consumibles_carne();
	void borrar_consumible(Consumible_Fuerza* objeto);
	void borrar_consumible(short id);

private:
	std::vector<Consumible*> _consumibles;
};

#endif /* SRC_CONSUMIBLE_MANAGER_H_ */
