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
	~Consumible_Manager();

	std::vector<Consumible*>* get_consumibles();
	std::vector<Consumible_Patata*> get_consumibles_patata();
	std::vector<Consumible_Carne*> get_consumibles_carne();
	void borrar_consumible(Consumible_Power_Up* objeto);
	void borrar_consumible(short id);
	Vector2 crear_posiciones_aleatorias();
	
	void anyadir_consumible(Vector2 posicion);
	
	void anyadir_consumible_patata(Vector2 posicion);
	void anyadir_consumible_carne(Vector2 posicion);
	void anyadir_consumible_agua(Vector2 posicion);
	void anyadir_consumible_fuerza(Vector2 posicion);
	void anyadir_consumible_inmunidad(Vector2 posicion);
	void crear_todos_consumibles_que_faltan();

private:

	float mult;
	std::vector<Consumible*> _consumibles;

	uint16_t numero_max;
};

#endif /* SRC_CONSUMIBLE_MANAGER_H_ */
