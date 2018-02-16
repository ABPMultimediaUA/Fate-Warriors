#include "Interactuable_Manager.h"

//#include "Interfaz/Interfaz.h"

#include "Llave.h"
#include "Puerta.h"
#include "Interruptor.h"
#include "Puerta_Pincho.h"
#include "Zonas_Manager.h"
#include "Game.h"
#include "Datos_Partida.h"
#include "Zona.h"

Interactuable_Manager::Interactuable_Manager(Zona** _todas_las_zonas) {
    // tener xml con la informacion de todos los objetos
    
	_n_llaves = 1;
	_n_puertas = 1;
	_n_interruptores = 1;
	_n_puertas_pincho = 1;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
	_interruptores = new Interruptor*[_n_interruptores];
	_puertas_pincho = new Puerta_Pincho*[_n_puertas_pincho];
    
    unsigned short _cont;

	//for(_cont = 0; _cont < _n_llaves; _cont++) {
		//_llaves[_cont] = new Llave(20,0,10,230,25);
	//}
	
	//for(_cont = 0; _cont < _n_puertas; _cont++) {
		//_puertas[_cont] = new Puerta(25,0,10,-180,false);
	//}

	float mult = 4.9212625;
    
    
    //_llaves[1] = new Llave(0,10*mult,1*mult,10*mult,1);
    
    _puertas[0] = new Puerta(1,18*mult,0*mult, 31.5*mult,false);

   //_puertas[1] = new Puerta(127,-0,0,-180,false);
	
	_llaves[0] = new Llave(0, 5*mult, 0*mult, 37*mult,_puertas[0]->get_id());
/*
	Game* game 		= Game::game_instancia();
	Datos_Partida * datos	= game->game_get_datos();
	Zonas_Manager* zonas = datos->get_zonas_manager();
	Zona** todas_las_zonas = zonas->get_zonas();
*/
	_puertas_pincho[0] = new Puerta_Pincho(0,12.5*mult,20,23.5*mult, _todas_las_zonas[0], _todas_las_zonas[2]);	//Entre la sala 1 y 7
	_interruptores[0] = new Interruptor(0,15*mult,0,15*mult,_puertas_pincho[0],false,false, 500);

}

Interactuable_Manager::~Interactuable_Manager() {
    unsigned short _cont;
    
	for(_cont = 0; _cont < _n_llaves; _cont++) {
		delete _llaves[_cont];
	}
	delete [] _llaves;
    
    for(_cont = 0; _cont < _n_puertas; _cont++) {
		delete _puertas[_cont];
	}
	delete [] _puertas;

    for(_cont = 0; _cont < _n_interruptores; _cont++) {
		delete _interruptores[_cont];
	}
	delete [] _interruptores;


    for(_cont = 0; _cont < _n_puertas_pincho; _cont++) {
		delete _puertas_pincho[_cont];
	}
	delete [] _puertas_pincho;

}


void Interactuable_Manager::update_interruptores(){

	for(unsigned short cont=0; cont<_n_interruptores; cont++){
		_interruptores[cont]->update();
	}
}


Puerta_Pincho** Interactuable_Manager::get_puertas_pincho(){
	return _puertas_pincho;
}

Llave** Interactuable_Manager::get_llaves(){
	return _llaves;
}

Puerta** Interactuable_Manager::get_puertas(){
	return _puertas;
}

Interruptor** Interactuable_Manager::get_interruptores(){
	return _interruptores;
}

unsigned short Interactuable_Manager::get_n_llaves(){
	return _n_llaves;
}

unsigned short Interactuable_Manager::get_n_puertas(){
	return _n_puertas;
}

unsigned short Interactuable_Manager::get_n_interruptores(){
	return _n_interruptores;
}

unsigned short Interactuable_Manager::get_n_puertas_pincho(){
	return _n_puertas_pincho;
}

