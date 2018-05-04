#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

#include "Input/Input.h"

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
class Player;
class Interfaz_sonido;
class Zonas_Manager;
class Interactuable_Manager;
class Interruptor;

class Menu_Principal;
class Menu_Pausa;
class Menu_Fin;

class UI;

class Animacion_Interruptor;

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
    inline Input* get_input() { return _input_jugador;}

    void recibir_inputs() { _input_jugador->recibir_inputs();}

    // Funciones de cambio de Update
    void cambio_a_update_menu();
    void cambio_a_update_partida();
    void cambio_a_update_pausa();
    void cambio_a_update_win();
    void cambio_a_update_lose();
    void cambio_a_update_mirar(uint32_t _t_fin, Interruptor* _objetivo, short _rotacion_x, short _rotacion_y, short _distancia);
	Consumible_Action* get_consumibles_action();

	inline Menu_Principal* get_menu_principal(){ return _menu_principal; }

private:
	static Game* instancia;
	Game();

	

	void (Game::*update_actual)(double);
	void (Game::*render_actual)(float);

	void update_menu(double _i_tiempo_desde_ultimo_update);			// Update del menu
	void update_partida(double _i_tiempo_desde_ultimo_update);		// Update de partida
	void update_pausa(double _i_tiempo_desde_ultimo_update);		// Update de pausa
	void update_fin_partida(double _i_tiempo_desde_ultimo_update);	// Update de fin de partida
	void update_mirar(double _i_tiempo_desde_ultimo_update);		// Update de mirar a un objetivo

	void render_menu(float _i_interpolacion);						// Render del menu
	void render_partida(float _i_interpolacion);					// Render de partida
	void render_pausa(float _i_interpolacion);						// Render de pausa
	void render_win(float _i_interpolacion);						// Render de fin de partida (win)
	void render_lose(float _i_interpolacion);						// Render de fin de partida (lose)


	Player* _player;
	UI* _ui;
	Nivel* _nivel;
	Zonas_Manager* _zonas_manager;
	Interactuable_Manager* _interactuable_manager;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Decision_Manager *_decision_manager; 	// Encargado de tomar las decisiones de los NPCs
	Motor* _motor;
	Interfaz_sonido *_sonido;
	Consumible_Action * _consumibles_action;
	Trampas_action* _trampas_action;
	Input* _input_jugador;

	Menu_Principal* _menu_principal;		// Menu Principal
	Menu_Pausa* _menu_pausa;				// Menu Pausa
	Menu_Fin*	_menu_fin;					// Menu Fin Partida

	Animacion_Interruptor* _animacion_interruptor;
};


#endif /* HEADER_GAME_H_ */
