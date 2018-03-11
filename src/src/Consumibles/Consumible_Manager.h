#ifndef SRC_CONSUMIBLE_MANAGER_H_
#define SRC_CONSUMIBLE_MANAGER_H_

#include <vector>
#include <cstdint>
#include "../Utilidades/Vector.h"


class Consumible;
class Consumible_Carne;
class Consumible_Patata;
class Consumible_Power_Up;
class Time;

class Consumible_Manager{
public:
	Consumible_Manager();
	virtual ~Consumible_Manager();

	std::vector<Consumible*>* get_consumibles();
	std::vector<Consumible_Patata*> get_consumibles_patata();
	std::vector<Consumible_Carne*> get_consumibles_carne();
	void borrar_consumible(Consumible_Power_Up* objeto);
	void borrar_consumible(short id);
	Vector2 crear_posiciones_aleatorias();
	void anyadir_consumible();
	
	void anyadir_consumible_patata();
	void anyadir_consumible_carne();
	void anyadir_consumible_agua();
	void anyadir_consumible_fuerza();
	void anyadir_consumible_inmunidad();
	void crear_todos_consumibles_que_faltan();

private:

	float mult;
	std::vector<Consumible*> _consumibles;
	std::vector<Vector2> posiciones_resp_por_usar;
	std::vector<double> tiempo_resp_por_usar;

	uint16_t numero_max;
	Time* _reloj;
	double _tiempo_ultimo_creado;
};

#endif /* SRC_CONSUMIBLE_MANAGER_H_ */
