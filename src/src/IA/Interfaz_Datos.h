#ifndef INTERFAZ_DATOS_H_
#define INTERFAZ_DATOS_H_

class Datos_Partida;
class NPC;
class NPC_Manager;

class Interfaz_Datos {
public:
	Interfaz_Datos();
	virtual ~Interfaz_Datos();

	float get_distancia_enemigo_personaje(unsigned short _i_n_enemigo);
	NPC** get_enemigos();
	NPC* get_enemigo(unsigned short _i_n_enemigo);
	unsigned short get_n_enemigos();
	void get_pos_player(float& _i_x, float& _i_y);
	void get_pos_enemigo(unsigned short _i_n_enemigo, float& _i_x, float& _i_y);

private:
	Datos_Partida* _datos;
	NPC_Manager* _npc_manager;
};

#endif /* INTERFAZ_DATOS_H_ */
