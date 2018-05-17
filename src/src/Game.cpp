#include "Game.h"

#include "Datos_Partida.h"

#include "IA/Action_Manager.h"
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
#include "Menus/Menu_Fin.h"
#include "Zonas/Zonas_Manager.h"
#include "Interactuables/Interactuable_Manager.h"
#include "Zonas/Respawn.h"

#include "Interactuables/Animacion_Interruptor.h"
#include "Interactuables/Interruptor.h"

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
    _sonido= Interfaz_sonido::GetInstancia();
	_sonido->Play_musica(0);
	_input_jugador = new Input();
	_motor->asigna_input(_input_jugador);

	_menu_principal = new Menu_Principal(_input_jugador);
	_menu_pausa = new Menu_Pausa(_input_jugador);
	_menu_fin = new Menu_Fin(_input_jugador);

	update_actual = &Game::update_menu;
	render_actual = &Game::render_menu;

	_input_jugador->asignar_teclas_menu();
	
}

Game::~Game(){
	delete _menu_pausa;
	delete _menu_principal;
	delete _menu_fin;

	delete _input_jugador;

	// Delete de singletons
	delete _sonido;
	delete _motor;
}


void Game::crea_partida() {	
	_motor->pantalla_carga();

	_nivel = Nivel::nivel_instancia();
	_sonido= Interfaz_sonido::GetInstancia();
	_motor->CargaMapa();
	Respawn::posiciones_instancia()->leer_posiciones_de_respawn_del_nivel();
	_datos 				= new Datos_Partida(_input_jugador);
	_action_manager 	= new Action_Manager();
	_decision_manager 	= new Decision_Manager(_action_manager);

	_zonas_manager		= _datos->get_zonas_manager();
	_interactuable_manager = _datos->get_interactuable_manager();

	_player = _datos->get_player();

	_datos->inserta_npc_nivel();
	
	_consumibles_action = new Consumible_Action();	
	_trampas_action 	= new Trampas_action();	

	//_datos->posicionar_characters_inicialmente();

	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;

	_input_jugador->asignar_teclas_partida();

	_animacion_interruptor = new Animacion_Interruptor();

	_player->carga_animaciones();

	//sonidos ambiente
	_sonido->Play_ambiente(3);
	_sonido->Play_ambiente(0);
}

void Game::fin_partida() {
	_motor->vaciar_motor();

	delete _datos;

	delete _decision_manager;

	delete _action_manager;
	
	delete _consumibles_action;

	delete _trampas_action;

	delete _nivel;

	_input_jugador->asignar_teclas_menu();
	
	

	Respawn::posiciones_instancia()->eliminar_datos();

	delete _animacion_interruptor;
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
	if(_input_jugador->get_pausa() && Time::Instance()->get_tiempo_inicio_pausa() > 200) {
		_sonido->Play_menu(3);
    	cambio_a_update_pausa();
    }
    else {
		 _motor->_interfaz->Update(_i_tiempo_desde_ultimo_update); 
		_player->update();
		_nivel->Update();
		_consumibles_action->comprobar_consumibles();
		_trampas_action->update();

		_motor->update(_i_tiempo_desde_ultimo_update);
		_interactuable_manager->update_interruptores();
		_decision_manager->toma_decisiones();
		_zonas_manager->actualizar_zonas();
    }
}


void Game::update_pausa(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Pausa" << std::endl;
	_menu_pausa->update(_i_tiempo_desde_ultimo_update);

    if(update_actual == &Game::update_partida) {
		_sonido->Play_menu(1);
		update_partida(_i_tiempo_desde_ultimo_update);	
    }
}


void Game::update_fin_partida(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Fin Partida" << std::endl;
	_menu_fin->update(_i_tiempo_desde_ultimo_update);

    if(update_actual == &Game::update_partida) {
		update_partida(_i_tiempo_desde_ultimo_update);	
    }
}


void Game::update_mirar(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Mirar" << std::endl;
	if(_animacion_interruptor->update(_i_tiempo_desde_ultimo_update) == true) {
		Motor::Motor_GetInstance()->poner_camara_a_entidad(_player->get_objeto_motor());
		cambio_a_update_partida();
	}
}


void Game::update_pre_partida(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Pre Partida" << std::endl;
	if(_input_jugador->get_saltar() && Time::Instance()->get_tiempo_inicio_pausa() > 500) {
   		Game::game_instancia()->cambio_a_update_partida();
		_sonido->Play_menu(0);
	}
}

// ------------------------------------ FUNCIONES DE RENDER ------------------------------------

void Game::render(float _i_interpolacion){
	(*this.*render_actual)(_i_interpolacion);
}

void Game::render_menu(float _i_interpolacion){
	_motor->render_Menu();
}

void Game::render_partida(float _i_interpolacion){
	_motor->render(_i_interpolacion);
}

void Game::render_pausa(float _i_interpolacion){
	_motor->render_Pausa();
}

void Game::render_win(float _i_interpolacion){
	_motor->render_Menu_Win();
}

void Game::render_lose(float _i_interpolacion){
	_motor->render_Menu_Lose();
}

void Game::render_pre_partida(float _i_interpolacion){
	_motor->render_partida_cargada();
}



// ------------------------------------ FUNCIONES DE CAMBIO DE ESTADO ------------------------------------

void Game::cambio_a_update_menu() {
	update_actual = &Game::update_menu;
	render_actual = &Game::render_menu;
	fin_partida();

    _sonido->Stop_pasos();
	_sonido->Stop_ambiente(3);
	_sonido->Stop_ambiente(4);
	_sonido->play_music(0);
}


void Game::cambio_a_update_partida() {
	_sonido->start_game_music();

	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;
	Time::Instance()->reanudar_reloj();
	_input_jugador->asignar_teclas_partida();
}

void Game::cambio_a_update_pausa() {
	if(update_actual != &Game::update_mirar) {
		update_actual = &Game::update_pausa;
		render_actual = &Game::render_pausa;
		_menu_pausa->set_tiempo_pausa();
		_input_jugador->asignar_teclas_menu();
        _sonido->Stop_pasos();
	}
}

void Game::cambio_a_update_win() {
	update_actual = &Game::update_fin_partida;
	render_actual = &Game::render_win;
	_menu_pausa->set_tiempo_pausa();
	_input_jugador->asignar_teclas_menu();

    _sonido->Stop_pasos();
	_sonido->play_music(9);
}

void Game::cambio_a_update_lose() {
	update_actual = &Game::update_fin_partida;
	render_actual = &Game::render_lose;
	_menu_pausa->set_tiempo_pausa();
	_input_jugador->asignar_teclas_menu();

    _sonido->Stop_pasos();
	_sonido->play_music(13);
}


void Game::cambio_a_update_mirar(uint32_t _t_fin, Interruptor* _objetivo, short _rotacion_x, short _rotacion_y, short _distancia) {
	update_actual = &Game::update_mirar;
	render_actual = &Game::render_partida;

	_sonido->Stop_pasos();
	_animacion_interruptor->empieza(_t_fin, _objetivo, _rotacion_x, _rotacion_y, 20);
}


void Game::cambio_a_update_pre_partida() {
	_input_jugador->asignar_teclas_menu();
	update_actual = &Game::update_pre_partida;
	render_actual = &Game::render_pre_partida;
	
	_menu_pausa->set_tiempo_pausa();
	Time::Instance()->reanudar_reloj();
}


void Game::set_llave_hud(bool _i_tiene_llave) {
	_motor->set_llave_hud(_i_tiene_llave);
}
/*Consumible_Action* Game::get_consumibles_action(){
	return _consumibles_action;
}*/