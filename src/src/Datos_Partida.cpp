#include "Datos_Partida.h"

#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"

Datos_Partida::Datos_Partida() {
	_jugador = new Player(0,0,30,0);

	_npc_manager = new NPC_Manager();

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    _interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
						"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
						0,0,0);


	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;

	delete _npc_manager;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida::get_npc_manager() {
	return _npc_manager;
}