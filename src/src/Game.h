#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

#include "Datos_Partida.h"
#include "Action_Manager.h"

class Game{

public:
	static Game* game_instancia();
	~Game();

	void game_crea_partida();
	void game_fin_partida();

	void game_run();

	Datos_Partida* game_get_datos();

private:
	static Game* instancia;

	Datos_Partida *_datos;
	Action_Manager *_action_manager;

	Game();

	void game_update();
	void game_render();
};


#endif /* HEADER_GAME_H_ */
