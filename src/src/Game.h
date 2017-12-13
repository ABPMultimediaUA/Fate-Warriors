#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

class Datos_Partida;
class Action_Manager;
class Decision_Manager;
class Datos_Partida;
class Trampas_action;
class Interfaz;
class Consumible_action;

class Game{

public:

	~Game();
	static Game* game_instancia();	
	void crea_partida();
	void fin_partida();
 	void update(double _i_tiempo_desde_ultimo_update);
	void render(float _i_interpolacion);
	void run();
  	Datos_Partida* game_get_datos();

private:

	Game();
	static Game* instancia;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Decision_Manager *_decision_manager; 	// Encargado de tomar las decisiones de los NPCs
	Interfaz *_interfaz_grafica;
	Trampas_action * _trampas_action;
	Consumible_action * _consumibles_action;
};


#endif /* HEADER_GAME_H_ */
