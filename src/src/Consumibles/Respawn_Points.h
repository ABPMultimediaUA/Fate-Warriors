#ifndef SRC_RESPAWN_POINTS_H_
#define SRC_RESPAWN_POINTS_H_

#include <vector>
#include <cstdint>
#include "../Utilidades/Vector.h"

class Time;
class Consumible_Manager;
class Armas_Manager;

class Respawn_Points{
public:
	Respawn_Points();
	void anyadir_nuevo_punto(Vector2 posicion);
	void generar_tipo_de_elemento();
	void anyadir_power_up();
	void anyadir_arma();

	void crear_ametralladora(Armas_Manager* _armas_manager);
	void crear_pistola(Armas_Manager* _armas_manager);
	void crear_katana(Armas_Manager* _armas_manager);

	void crear_consumible_patata(Consumible_Manager* _consumible_manager_);
	void crear_consumible_carne(Consumible_Manager* _consumible_manager_);
	void crear_consumible_agua(Consumible_Manager* _consumible_manager_);
	void crear_consumible_fuerza(Consumible_Manager* _consumible_manager_);
	
	~Respawn_Points();

private:
	std::vector<Vector2> posiciones_resp_por_usar;
	std::vector<double> tiempo_resp_por_usar;

	uint16_t numero_max;
	uint16_t cantidad_de_posiciones;
	float** posiciones;
	Time* _reloj;
	double _tiempo_ultimo_creado;
	Consumible_Manager* _consumible_manager;
};

#endif /* SRC_RESPAWN_POINTS_H_ */
