#include "Datos_Partida.h"

#include "Interactuable_Manager.h"
#include "Interfaz/Motor.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Consumibles/Consumible_Manager.h"
#include "Trampas/Trampas_manager.h"
#include "Llave.h"
#include "Puerta.h"
#include <iostream>


Datos_Partida::Datos_Partida(Input* _i_input) {
	float mult = 4.9212625;
	_jugador = new Player( 0, 15*mult, 50, 15*mult, _i_input);
	//Llave* _llave = new Llave(0,10*mult,1*mult,10*mult,1);
	//Puerta* _puerta = new Puerta(1,18*mult,1*mult,18*mult,false);
	_npc_manager = new NPC_Manager();
	_consumibles_manager = new Consumible_Manager();
	_trampas_manager	 = new Trampas_manager();
    _interactuable_manager = new Interactuable_Manager();
/*
	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    //_interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
	//					"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
	//					0,0,0);
	

	 
	_mapa = new Objeto_Estandar(1, 5*mult, 0, 5*mult, "models/Nodo1.zip", "Nodo1.obj");

	_mapa1 = new Objeto_Estandar(1, 11*mult, 0, 20*mult, "models/Pasillo6.zip", "Pasillo6.obj");
	_mapa2 = new Objeto_Estandar(1, 22*mult, 0, 21*mult, "models/Nodo3.zip", "Nodo3.obj");
	_mapa3 = new Objeto_Estandar(1, 20*mult, 0, 13*mult, "models/Pasillo2.zip", "Pasillo2.obj");
	_mapa4 = new Objeto_Estandar(1, 18*mult, 0, 30*mult, "models/Pasillo8.zip", "Pasillo8.obj");
	_mapa5 = new Objeto_Estandar(1, 30*mult, 0, 36*mult, "models/Pasillo4.zip", "Pasillo4.obj");
	_mapa6 = new Objeto_Estandar(1, 9*mult, 0, 42*mult, "models/Pasillo9.zip", "Pasillo9.obj");
	_mapa7 = new Objeto_Estandar(1, 3*mult, 0, 27*mult, "models/Nodo7.zip", "Nodo7.obj");
	_mapa8 = new Objeto_Estandar(1, 3*mult, 0, 49*mult, "models/Nodo10.zip", "Nodo10.obj");
	_mapa9 = new Objeto_Estandar(1, 38*mult, 0, 35*mult, "models/Nodo5.zip", "Nodo5.obj");


	_interfaz_grafica = nullptr;
	*/
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _trampas_manager;
	delete _consumibles_manager;
	/*delete _mapa;
	delete _mapa1;
	delete _mapa2;
	delete _mapa3;
	delete _mapa4;
	delete _mapa5;
	delete _mapa6;
	delete _mapa7;
	delete _mapa8;
	delete _mapa9;*/
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

Consumible_Manager * Datos_Partida::get_Consumible_Manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida::get_interactuable_manager(){
	return _interactuable_manager;
}
void Datos_Partida::inserta_npc_nivel(){
	_npc_manager->inserta_npc_nivel();
}