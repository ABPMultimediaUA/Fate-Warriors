#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

class Datos_Partida;
class Action_Manager;
class Decision_Manager;
class Datos_Partida;
class Interfaz;
class Interfaz_Fisica;
class Input;
class Consumible_action;
class Trampas_action;
class Nivel;
class Motor;

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
    Action_Manager* game_get_action_manager();

    void recibir_inputs();

private:

	Game();
	static Game* instancia;
	Nivel* _nivel;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Decision_Manager *_decision_manager; 	// Encargado de tomar las decisiones de los NPCs
	Motor* _motor;
	Consumible_action * _consumibles_action;
	Trampas_action* _trampas_action;
	Input* _input_jugador;
};


#endif /* HEADER_GAME_H_ */
