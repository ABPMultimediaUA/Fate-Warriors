#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"

#include "Entrada/Controles.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Motor.h"
#include "Nivel/Nivel.h"
#include "Consumibles/Consumible_Action.h"
#include "Tiempo/Time.h"
#include "Trampas/Trampas_action.h"
#include "Motor_sonido/Interfaz_sonido.h"
#include "Menus/Menu_Principal.h"
#include "Menus/Menu_Pausa.h"
#include "Zonas_Manager.h"
#include "Interactuable_Manager.h"
#include "Respawn.h"

#include <iostream>
#include <stack>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia = new Game();

	return instancia;
}
Game::Game() : _datos(nullptr), 
			   _action_manager(nullptr), 
			   _decision_manager(nullptr), 
			   _consumibles_action(nullptr),
			   _trampas_action(nullptr) {
	_motor = Motor::Motor_GetInstance();

	_input_jugador = new Input();
	//_motor->asigna_input(_input_jugador);

	_menu_principal = new Menu_Principal(_input_jugador);
	_menu_pausa = new Menu_Pausa(_input_jugador);

	update_actual = &Game::update_menu;
	render_actual = &Game::render_menu;

	_input_jugador->asignar_teclas_menu();
}

Game::~Game(){
	delete _menu_pausa;
	delete _menu_principal;

	delete _input_jugador;

	// Delete de singletons
	delete _sonido;
	delete _motor;
}


void Game::crea_partida() {	
	_nivel = Nivel::nivel_instancia();
	_sonido=Interfaz_sonido::GetInstancia();
	_datos 				= new Datos_Partida(_input_jugador);
	_action_manager 	= new Action_Manager();
	_decision_manager 	= new Decision_Manager(_action_manager);

	_zonas_manager		= _datos->get_zonas_manager();
	_interactuable_manager = _datos->get_interactuable_manager();

	_player = _datos->get_player();
	_datos->inserta_npc_nivel();
	
	_consumibles_action = new Consumible_Action();	
	_trampas_action 	= new Trampas_action();	

	_datos->posicionar_characters_inicialmente();

	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;

	_input_jugador->asignar_teclas_partida();

	_tiempo_final_de_partida = Time::Instance()->get_current()+600000;
}

void Game::fin_partida() {
	delete _datos;

	delete _decision_manager;

	delete _action_manager;
	
	delete _consumibles_action;

	delete _trampas_action;

	delete _nivel;

	_input_jugador->asignar_teclas_menu();

	//_motor->vaciar_motor();
	Respawn* pointer = Respawn::posiciones_instancia();
	delete pointer;
	//Respawn::posiciones_instancia()->eliminar_datos();
}

// ------------------------------------ FUNCIONES DE UPDATE ------------------------------------

// Llama a la funcion update en el momento necesario
void Game::update(double _i_tiempo_desde_ultimo_update){
    // Procesa los inputs para poder utilizarlos
    _input_jugador->procesar_inputs();

    // Llamar al update adecuado
	(*this.*update_actual)(_i_tiempo_desde_ultimo_update);

    // Reinicia el procesado y lectura de inputs
    _input_jugador->reiniciar_inputs();
}


void Game::update_menu(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Menu" << std::endl;
	_menu_principal->update(_i_tiempo_desde_ultimo_update);
}


void Game::update_partida(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Partida" << std::endl;
	std::cout << "UPDATE\n";
	if(_input_jugador->get_pausa() && Time::Instance()->get_tiempo_inicio_pausa() > 200) {
    	cambio_a_update_pausa();
    }
    else {
			_player->update();
			_nivel->Update();
			//_consumibles_action->comprobar_consumibles();
			//_trampas_action->update();

			_motor->update(_i_tiempo_desde_ultimo_update);
			//_interactuable_manager->update_interruptores();
			//_decision_manager->toma_decisiones();
			_zonas_manager->actualizar_zonas();

			if(Time::Instance()->get_current()>_tiempo_final_de_partida){
				_zonas_manager->comprobar_victoria_fin_tiempo_partida();
				cambio_a_update_menu();
				//Fin de partida
			}
			else{
				if(_zonas_manager->comprobar_victoria()!=Enum_Equipo_Ninguno){
					cambio_a_update_menu();
				}
				//if equipo!=neutro Fin partida
			}
    }
}


void Game::update_pausa(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Pausa" << std::endl;
	_menu_pausa->update(_i_tiempo_desde_ultimo_update);

    if(update_actual == &Game::update_partida) {
		update_partida(_i_tiempo_desde_ultimo_update);	
    }
}


// ------------------------------------ FUNCIONES DE RENDER ------------------------------------

void Game::render(float _i_interpolacion){
	(*this.*render_actual)(_i_interpolacion);
}

void Game::render_menu(float _i_interpolacion){
}

void Game::render_partida(float _i_interpolacion){
	std::cout << "RENDER\n";
	_motor->render(1);
}

void Game::render_pausa(float _i_interpolacion){
	_motor->render(1);
}



// ------------------------------------ FUNCIONES DE CAMBIO DE ESTADO ------------------------------------

void Game::cambio_a_update_menu() {
	update_actual = &Game::update_menu;
	render_actual = &Game::render_menu;
	fin_partida();
}


void Game::cambio_a_update_partida() {
	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;
	Time::Instance()->reanudar_reloj();
	_input_jugador->asignar_teclas_partida();
}

void Game::cambio_a_update_pausa() {
	update_actual = &Game::update_pausa;
	render_actual = &Game::render_pausa;
	_menu_pausa->set_tiempo_pausa();
	_input_jugador->asignar_teclas_menu();
}


Consumible_Action* Game::get_consumibles_action(){
	return _consumibles_action;
}