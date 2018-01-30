#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

#include "Input.h"

class Datos_Partida;
class Action_Manager;
class Decision_Manager;
class Datos_Partida;
class Interfaz;
class Interfaz_Fisica;
class Consumible_Action;
class Trampas_action;
class Nivel;
class Motor;
class Interfaz_sonido;

class Game{

public:
	static Game* game_instancia();	
	~Game();

	void crea_partida();
	void fin_partida();

 	void update(double _i_tiempo_desde_ultimo_update);	// Update publico

	void render(float _i_interpolacion);				// Render publico

  	inline Datos_Partida* game_get_datos() { return _datos;}
    inline Action_Manager* game_get_action_manager() { return _action_manager;}

    void recibir_inputs() { _input_jugador->recibir_inputs();}

    // Funciones de cambio de Update
    void cambio_a_update_menu();
    void cambio_a_update_partida();
    void cambio_a_update_pausa();
	Consumible_Action* get_consumibles_action();

private:
	static Game* instancia;
	Game();

	void (Game::*update_actual)(double);
	void (Game::*render_actual)(float);

	void update_menu(double _i_tiempo_desde_ultimo_update);			// Update del menu
	void update_partida(double _i_tiempo_desde_ultimo_update);		// Update de partida
	void update_pausa(double _i_tiempo_desde_ultimo_update);		// Update de pausa

	void render_menu(float _i_interpolacion);						// Render del menu
	void render_partida(float _i_interpolacion);					// Render de partida
	void render_pausa(float _i_interpolacion);						// Render de pausa

	Nivel* _nivel;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Decision_Manager *_decision_manager; 	// Encargado de tomar las decisiones de los NPCs
	Motor* _motor;
	Interfaz_sonido *_sonido;
	Consumible_Action * _consumibles_action;
	Trampas_action* _trampas_action;
	Input* _input_jugador;
};


#endif /* HEADER_GAME_H_ */
