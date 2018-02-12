#ifndef SRC_ARMAS_MANAGER_H_
#define SRC_ARMAS_MANAGER_H_

#include <vector>
#include "../Utilidades/Vector.h"

class Arma;
class Proyectil;


class Armas_Manager{
public:
	Armas_Manager();
	virtual ~Armas_Manager();

	std::vector<Arma*>* get_armas();

	void borrar_arma(Arma* objeto);
	void borrar_arma(short id);

	void anyadir_proyectil(Proyectil* _i_bala);
	void borrar_proyectil(Proyectil* objeto);

	void crear_ametralladora(Vector2 posicion);
	void crear_pistola(Vector2 posicion);
	void crear_katana(Vector2 posicion);

private:
	std::vector<Arma*> _armas;
	std::vector<Proyectil*> _balas;
};

#endif /* SRC_ARMAS_MANAGER_H_ */
