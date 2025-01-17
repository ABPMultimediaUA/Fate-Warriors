#ifndef ZONAS_MANAGER_H_
#define ZONAS_MANAGER_H_

#include "../Personajes/Enum_Tipo_Ataque.h"
#include "../Utilidades/Vector.h"

#include <vector>
#include <cstdint>
#include <tuple>

class Zona;
class Zona_Inicial;
class Player;

class Zonas_Manager {
public:
	Zonas_Manager();
	~Zonas_Manager();

	void actualizar_zonas();
	Zona** get_zonas();

	std::tuple<uint8_t,uint8_t> calcular_cantidad_territorios_por_bando();
	Enum_Equipo comprobar_victoria();
	Enum_Equipo comprobar_victoria_fin_tiempo_partida();
    
	unsigned short get_n_zonas();

	Vector2 get_posicion_zona_inicial();

	
private:
	Zona** _zonas;

	Zona_Inicial* _zona_incial;

	unsigned short _n_zonas;
	uint8_t _equipoA;
	uint8_t _equipoB;
};

#endif /* ZONAS_MANAGER_H_ */
