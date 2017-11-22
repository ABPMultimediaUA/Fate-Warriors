#ifndef INTERFAZ_TOMA_DECISION_H_
#define INTERFAZ_TOMA_DECISION_H_

#include "Datos_Partida.h"

class Interfaz_Toma_Decision {
public:
	Interfaz_Toma_Decision();
	virtual ~Interfaz_Toma_Decision();

	float interfaz_decision_distancia_enemigo_personaje(unsigned short _i_n_enemigo);
	NPC** interfaz_decision_get_enemigos();
	NPC* interfaz_decision_get_enemigo(unsigned short _i_n_enemigo);
	unsigned short interfaz_decision_get_n_enemigos();
	void interfaz_decision_get_pos_player(float& _i_x, float& _i_y);
	void interfaz_decision_get_pos_enemigo(unsigned short _i_n_enemigo, float& _i_x, float& _i_y);

private:
	Datos_Partida* _datos;
};

#endif /* INTERFAZ_TOMA_DECISION_H_ */
