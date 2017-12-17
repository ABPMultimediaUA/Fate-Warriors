#include "Datos_Partida.h"

#include "Llave.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Objeto_Estandar.h"
#include "Personajes/NPC_Manager.h"


Datos_Partida::Datos_Partida() {
	float mult = 39.3701;
	_jugador = new Player(0,-15*mult,100,15*mult);
	_npc_manager = new NPC_Manager();

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    //_interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
	//					"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
	//					0,0,0);
	

	//Objeto_Estandar* _mapa = new Objeto_Estandar(1, 0, 0, 0, "models/Nivel1_t.zip", "Nivel1_t.obj"); 
	 
	Objeto_Estandar* _mapa = new Objeto_Estandar(1, -5*mult, 0, 5*mult, "models/Nodo2.zip", "Nodo1.obj");


	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _mapa;
	//delete llavecita;
	delete _npc_manager;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida::get_npc_manager() {
	return _npc_manager;
}