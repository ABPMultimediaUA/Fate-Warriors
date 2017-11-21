#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_


#include "Enemy.h"
#include "Hero.h"
#include "Input.h"


class Game{

public:
	~Game();
	void game_run(); //hola mundo
	static Game* getInstance();
	void main_loop_servidor();
	void main_loop_cliente();
	void anyadir_jugador();
	void actualizar_jugador_coop(float x, float y);
	void actualizar_by_id(short id, Input_key actionkey);
	void actualizar_posicion_enemigo(float x, float y, short id);
	
private:
	Game();
	static  Game* instancia;
	Enemy *enemigo1;
	Hero**yoplayer;

private:
	void game_update();
	void game_render();

};


#endif /* HEADER_GAME_H_ */
