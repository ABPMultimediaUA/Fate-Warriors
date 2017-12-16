#ifndef SRC_Consumible_manager_H_
#define SRC_Consumible_manager_H_

#include <vector>

class Consumible;
class Consumible_carne;
class Consumible_patata;


class Consumible_manager{
public:
	Consumible_manager();
	virtual ~Consumible_manager();

	std::vector<Consumible*>* get_consumibles();
	std::vector<Consumible_patata*> get_consumibles_patata();
	std::vector<Consumible_carne*> get_consumibles_carne();
	void borrar_consumible(Consumible* objeto);
	void borrar_consumible(short id);

private:
	std::vector<Consumible*> _consumibles;
};

#endif /* SRC_Consumible_manager_H_ */
