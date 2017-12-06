#include "Datos_Partida.h"

#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Personajes/NPC.h"
#include "Armas/AD_Ametralladora.h"
#include "Triggers/Trigger_zona_vida.h"

Datos_Partida::Datos_Partida() {
	_jugador = new Player(0,0,30,0);

	_n_enemigos = 1;

	_npc = new NPC*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_npc[_cont] = new NPC(0,19,0,0,5,15);
	}

	Vector2 aa = Vector2(0,0);

	trigger_zona_vida1 = new Trigger_zona_vida(aa);

	_ametralladora = new AD_Ametralladora(1,1,1,1);

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    _interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
						"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
						0,0,0);


	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete trigger_zona_vida1;
	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

unsigned short Datos_Partida::get_n_enemigos(){
	return _n_enemigos;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC** Datos_Partida::get_npcs(){
	return _npc;
}

Trigger_zona_vida* Datos_Partida::get_trigger(){
	return trigger_zona_vida1;
}