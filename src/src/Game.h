#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

class Datos_Partida;
class Action_Manager;
class Decision_Manager;
class Datos_Partida;
class Interfaz;
class Interfaz_Fisica;
class Input;
class Consumible_Action;
class Trampas_action;
class Nivel;
class Motor;

class Game{

public:
	static Game* game_instancia();	
	~Game();

	void crea_partida();
	void fin_partida();

 	void update(double _i_tiempo_desde_ultimo_update);	// Update publico

	void render(float _i_interpolacion);				// Render publico

	void run();
  	Datos_Partida* game_get_datos();
    Action_Manager* game_get_action_manager();

    void recibir_inputs();

    // Funciones de cambio de Update
    void cambio_a_update_partida();
    void cambio_a_update_pausa();

private:
	static Game* instancia;
	Game();

	void (Game::*update_actual)(double);
	void (Game::*render_actual)(float);

	void update_partida(double _i_tiempo_desde_ultimo_update);		// Update de partida
	void update_pausa(double _i_tiempo_desde_ultimo_update);		// Update de pausa

	void render_partida(float _i_interpolacion);		// Render de partida
	void render_pausa(float _i_interpolacion);		// Render de pausa

	Nivel* _nivel;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Decision_Manager *_decision_manager; 	// Encargado de tomar las decisiones de los NPCs
	Motor* _motor;
	Consumible_Action * _consumibles_action;
	Trampas_action* _trampas_action;
	Input* _input_jugador;
};


#endif /* HEADER_GAME_H_ */
