#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_


#include "Datos_Partida.h"
#include "Action_Manager.h"
#include "Enemy.h"
#include "Hero.h"
#include "Input.h"



class Game{

public:

	~Game();
	void game_run(); //hola mundo
	static Game* game_instancia();
	void main_loop_servidor();
	void main_loop_cliente();
	void anyadir_jugador();
	void actualizar_jugador_coop(float x, float y);
	void actualizar_by_id(short id, Input_key actionkey);
	void actualizar_posicion_enemigo(float x, float y, short id);
	void game_crea_partida();
	void game_fin_partida();
  void game_update();
	void game_render();
	void game_run();
  Datos_Partida* game_get_datos();
private:
	Game();

	Enemy *enemigo1;
	Hero**yoplayer;

	static Game* instancia;

	Datos_Partida *_datos;
	Action_Manager *_action_manager;



};


#endif /* HEADER_GAME_H_ */
