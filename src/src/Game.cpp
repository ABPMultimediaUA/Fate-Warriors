#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"

#include "Entrada/Input.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Interfaz.h"
#include "Nivel/Nivel.h"

#include <iostream>
#include <stack>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}
Game::Game() : _datos(nullptr), _action_manager(nullptr), _decision_manager(nullptr), _interfaz_grafica(nullptr){

}

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
	if(_interfaz_grafica != nullptr) {
		delete _interfaz_grafica;
		_interfaz_grafica = nullptr;
	}
}


void Game::crea_partida() {	
	_interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
	_datos = new Datos_Partida();
	_action_manager = new Action_Manager();
	_decision_manager = new Decision_Manager(_action_manager);

	//cargar nivel 1
	std::string nivel="txt/Nivel/Nivel1.txt";
	Nivel* _nivel1=new Nivel(nivel);

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

	//std::cout << _nivel1->nivel_pathfindinglod1(14.5,20,14.5,25.5)<<std::endl;
/*
	std::cout << _nivel1->nivel_pathfindinglod1(11,11,14.5,25.5)<<std::endl;

	std::cout << _nivel1->nivel_pathfindinglod1(12.5,12.5,14.5,25.5)<<std::endl;

	std::cout << _nivel1->nivel_pathfindinglod1(8,10,14.5,25.5)<<std::endl;*/

	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Hola, soy un main  pa probar cosas. Empecemos:" << std::endl;
	std::cout << "Primero vamos por algo facil, un camino entre vertices de un nodo:" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Nodo 1, vertice 15 hacia el 9: "<< _nivel1->nivel_pathfindinglod1(8,15,17,10) << "º -> "
	<< _nivel1->nivel_pathfindinglod1(11,14,17,10) << "º -> "<< _nivel1->nivel_pathfindinglod1(12.5,12.5,17,10) << 
	"º -> " << _nivel1->nivel_pathfindinglod1(14,11,17,10) << "º" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Vale, reconozco que eso ha sido facil, vamos con algo mas dificil:" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Vamos a ir de un nodo a un pasillo, por ejemplo, del Nodo1 hacia el Pasillo6:" << std::endl;
	std::cout << "Nodo 1, vertice 18 hacia el Pasillo6, vertice 2: "<< _nivel1->nivel_pathfindinglod1(15,17,23.5,12.5) <<"º -> "
	<< _nivel1->nivel_pathfindinglod1(17,15,23.5,12.5) << "º -> "<< _nivel1->nivel_pathfindinglod1(19,12.5,23.5,12.5) << 
	"º -> " << _nivel1->nivel_pathfindinglod1(21,12.5,23.5,12.5)<< "º" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Vaya, funciona!!!!, vamos con otra cosa:" << std::endl;
	std::cout << "Vamos con un camino dentro de un mismo nodo, con x e y diferentes a los vertices:" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Nodo 1, vertice 15 hacia el 9, pero con coordenadas fuera del grafo: "<< _nivel1->nivel_pathfindinglod1(7,15,17,10) << "º -> "
	<< _nivel1->nivel_pathfindinglod1(11,14,17,10) << "º -> "<< _nivel1->nivel_pathfindinglod1(12.5,12.5,17,10) << 
	"º -> " << _nivel1->nivel_pathfindinglod1(14,11,16,9)<< "º" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Vamos con un camino de un nodo a un pasillo, con x e y diferentes a los vertices:" << std::endl;
	std::cout << "Nodo 1, vertice 14,18 hacia el Pasillo6, vertice 22,15: "<< _nivel1->nivel_pathfindinglod1(14,18,22,12) <<"º -> "
	<< _nivel1->nivel_pathfindinglod1(17,15,22,12) << "º -> "<< _nivel1->nivel_pathfindinglod1(19,12.5,22,12) << 
	"º -> " << _nivel1->nivel_pathfindinglod1(21,12.5,22,12)<< "º" << std::endl;
	std::cout << "---------***************-----------------**************------------------" << std::endl;
	std::cout << "Bueno, ha sido un placer, nos vemos en otro main :D" << std::endl;
	
	
	
	
	
	delete _nivel1;

}

void Game::fin_partida() {
	delete _datos;
	delete _decision_manager;
	delete _action_manager;
	delete _interfaz_grafica;

	_datos = nullptr;
	_decision_manager = nullptr;
	_action_manager = nullptr;
	_interfaz_grafica = nullptr;
}

void Game::run(){

}


void Game::update(double _i_tiempo_desde_ultimo_update){
	Player *_player = _datos->get_player();
	_player->update();
	_player = nullptr;
	_decision_manager->toma_decisiones();
}

void Game::render(float _i_interpolacion){
	_interfaz_grafica->Interfaz_Update(); //Camara->update();
	_interfaz_grafica->Interfaz_Render();
}
  
Datos_Partida* Game::game_get_datos() {
	return _datos;
}