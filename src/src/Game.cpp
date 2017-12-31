#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"

#include "Entrada/Input.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Motor.h"
#include "Nivel/Nivel.h"
#include "Consumibles/Consumible_action.h"
#include "Trampas/Trampas_action.h"


#include <iostream>
#include <stack>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}
Game::Game() : _datos(nullptr), 
			   _action_manager(nullptr), 
			   _decision_manager(nullptr), 
			   _motor(nullptr),
			   _consumibles_action(nullptr),
			   _trampas_action(nullptr)
			   {}

Game::~Game(){

	if(_datos != nullptr) {
		delete _datos;
		_datos = nullptr;
	}
	if(_decision_manager != nullptr) {
		delete _decision_manager;
		_decision_manager = nullptr;
	}
	if(_action_manager != nullptr) {
		delete _action_manager;
		_action_manager = nullptr;
	}
	if(_motor != nullptr) {
		delete _motor;
		_motor = nullptr;
	}
	if(_consumibles_action != nullptr) {
		delete _consumibles_action;
		_consumibles_action = nullptr;
	}

	if(_trampas_action != nullptr) {
		delete _consumibles_action;
		_consumibles_action = nullptr;
	}
}


void Game::crea_partida() {	

	_motor = Motor::Motor_GetInstance();
	_nivel=Nivel::nivel_instancia();
	_datos 				= new Datos_Partida();
	_action_manager 	= new Action_Manager();
	_decision_manager 	= new Decision_Manager(_action_manager);

	
	_consumibles_action = new Consumible_action();	
	_trampas_action 	= new Trampas_action();	
	


	//cargar nivel 1
	/*
	std::string nivel="txt/Nivel/Nivel1.txt";

	/*_nivel1->nivel_set_lod(3);

	stack<Vertice*> algo2=_nivel1->nivel_camino_corto_l2(_nivel1->nivel_get_vertice(5),_nivel1->nivel_get_vertice(32));
	Vertice *pv2;
                    
                    while(!algo2.empty()){
                        pv2=algo2.top();
                        std::cout << pv2->_id <<" -> ";
						std::cout << pv2->_lod <<" * ";
                        algo2.pop();
                    }
                    std::cout<<std::endl;
	std::cout <<_nivel1->nivel_get_nodo(7)->_blackboard->get_zonas_ady()[0] <<std::endl;
	std::cout << _nivel1->nivel_get_id_vertice(67,27)<<std::endl;*/

}

void Game::fin_partida() {

	//delete _datos;   ->da core dumped amigos
	delete _decision_manager;
	delete _action_manager;
	
	delete _motor;
	delete _consumibles_action;
	delete _trampas_action;
	delete _nivel;


	_datos 				= nullptr;
	_decision_manager 	= nullptr;
	_action_manager 	= nullptr;
	_consumibles_action = nullptr;
	_trampas_action 	= nullptr;
	_motor = nullptr;
}

void Game::run(){

}


void Game::update(double _i_tiempo_desde_ultimo_update){
	//std::cout << "UPDATE" << std::endl;
	Player *_player = _datos->get_player();
	_player->update();
	_nivel->Update();
	//_consumibles_action->comprobar_consumibles();
	//_trampas_action->update();
	_player = nullptr;

	_motor->update(_i_tiempo_desde_ultimo_update);
		
//std::cout<<"ALTURA:    "<<_interfaz_grafica->getHeight()<<std::endl;
	_decision_manager->toma_decisiones();
}

void Game::render(float _i_interpolacion){
	//std::cout << "YEEEEEEEEEE" << std::endl;
	_motor->render();
}
  
Datos_Partida* Game::game_get_datos() {
	return _datos;
}

Action_Manager* Game::game_get_action_manager() {
	return _action_manager;
}
