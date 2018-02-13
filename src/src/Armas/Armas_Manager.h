#ifndef SRC_ARMAS_MANAGER_H_
#define SRC_ARMAS_MANAGER_H_

#include <vector>
#include "../Utilidades/Vector.h"
#include <cstdint>

class Arma;
class Proyectil;
class Time;


class Armas_Manager{
public:
	Armas_Manager();
	virtual ~Armas_Manager();

	std::vector<Arma*>* get_armas();

	void borrar_arma(Arma* objeto);
	void borrar_arma(short id);

	void anyadir_proyectil(Proyectil* _i_bala);
	void borrar_proyectil(Proyectil* objeto);

	void crear_ametralladora();
	void crear_pistola();
	void crear_katana();

	void anyadir_arma();
	void crear_todas_las_armas_que_faltan();
	Vector2 crear_posiciones_aleatorias();

private:
	std::vector<Arma*> _armas;
	std::vector<Proyectil*> _balas;
	uint8_t _numero_max;

	uint16_t numero_max;
	uint16_t cantidad_de_posiciones;
	float** posiciones;
	Time* _reloj;
	double _tiempo_ultimo_creado;
};

#endif /* SRC_ARMAS_MANAGER_H_ */
