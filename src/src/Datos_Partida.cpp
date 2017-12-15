#include "Datos_Partida.h"

#include "Llave.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Objeto_Estandar.h"
#include "Personajes/NPC_Manager.h"


Datos_Partida::Datos_Partida() {

	_jugador = new Player(0,30,230,0);
	_npc_manager = new NPC_Manager();

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    //_interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
	//					"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
	//					0,0,0);
	
	//Objeto_Estandar* mapa = new Objeto_Estandar(1, 0, 0, 0, "models/Gilipollas.zip", "ManuManco.obj"); 
	Objeto_Estandar* _mapa = new Objeto_Estandar(1, 0, 0, 0, "models/Nivel1_t.zip", "Nivel1_t.obj"); 
	//Llave* llavecita = new Llave(0,0,10,230,0); 
	//_interfaz_grafica->Interfaz_cargaModeloZip("Nodo1.zip","Nodo1.obj",false,0,0,0);


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