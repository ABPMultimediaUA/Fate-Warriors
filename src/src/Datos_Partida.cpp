#include "Datos_Partida.h"

#include "Interactuable_Manager.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Objeto_Estandar.h"
#include "Personajes/NPC_Manager.h"
#include "Consumibles/Consumible_manager.h"
#include "Trampas/Trampas_manager.h"



Datos_Partida::Datos_Partida() {
	float mult = 39.3701;
	_jugador = new Player(0,15*mult,100,15*mult, 100, 10000, 5, 10);
	_npc_manager = new NPC_Manager();

	_consumibles_manager = new Consumible_manager();
	_trampas_manager	 = new Trampas_manager();
    _interactuable_manager = new Interactuable_Manager();

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    //_interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
	//					"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
	//					0,0,0);
	

	 
	Objeto_Estandar* _mapa = new Objeto_Estandar(1, 5*mult, 0, 5*mult, "models/Nodo1.zip", "Nodo1.obj");

	//Objeto_Estandar* _mapa1 = new Objeto_Estandar(1, 11*mult, 0, 20*mult, "models/Pasillo6.zip", "Pasillo6.obj");


	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _trampas_manager;
	delete _consumibles_manager;
	delete _mapa;
	//delete _mapa1;
	delete _npc_manager;
  delete _interactuable_manager;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida::get_npc_manager() {
	return _npc_manager;
}

Trampas_manager * Datos_Partida::get_trampas_manager(){
	return _trampas_manager;
}

Consumible_manager * Datos_Partida::get_consumible_manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida::get_interactuable_manager(){
	return _interactuable_manager;
}
