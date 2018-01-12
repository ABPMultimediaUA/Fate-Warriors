#ifndef SRC_ARMAS_MANAGER_H_
#define SRC_ARMAS_MANAGER_H_

#include <vector>

class Arma;


class Armas_Manager{
public:
	Armas_Manager();
	virtual ~Armas_Manager();

	std::vector<Arma*>* get_armas();

	void borrar_arma(Arma* objeto);
	void borrar_arma(short id);

private:
	std::vector<Arma*> _armas;
};

#endif /* SRC_ARMAS_MANAGER_H_ */
