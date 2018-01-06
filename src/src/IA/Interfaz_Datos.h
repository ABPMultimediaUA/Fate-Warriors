#ifndef INTERFAZ_DATOS_H_
#define INTERFAZ_DATOS_H_

#include <cstdint>

class Datos_Partida;
class NPC;
class NPC_Manager;

class Interfaz_Datos {
public:
	Interfaz_Datos();
	virtual ~Interfaz_Datos();

	float get_distancia_enemigo_personaje(uint16_t _i_n_enemigo);
	NPC** get_enemigos();
	NPC* get_enemigo(uint16_t _i_n_enemigo);
	uint16_t get_n_enemigos();
	void get_pos_player(float& _i_x, float& _i_y);
	void get_pos_enemigo(uint16_t _i_n_enemigo, float& _i_x, float& _i_y);

private:
	Datos_Partida* _datos;
	NPC_Manager* _npc_manager;
};

#endif /* INTERFAZ_DATOS_H_ */
