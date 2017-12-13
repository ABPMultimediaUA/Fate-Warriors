#include "Datos_Partida.h"

#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Trampas/Trampas_manager.h"
#include "Consumibles/Consumible_manager.h"

Datos_Partida::Datos_Partida() {
	_jugador = new Player(0,0,30,0);

	_npc_manager = new NPC_Manager();
	
	_trampas_manager = new Trampas_manager();

	_consumibles_manager = new Consumible_manager();

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    _interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
						"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
						0,0,0);


	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _trampas_manager;
	delete _npc_manager;
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