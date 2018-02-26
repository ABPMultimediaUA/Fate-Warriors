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
	_n_interruptores = 10;
	_n_puertas_pincho = 5;

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
    
    _puertas[0] = new Puerta(1,18*mult,0*mult, 31.5*mult,false, 8);

   //_puertas[1] = new Puerta(127,-0,0,-180,false);
	
	_llaves[0] = new Llave(0, 5*mult, 0*mult, 37*mult,_puertas[0]->get_id());
/*
	Game* game 		= Game::game_instancia();
	Datos_Partida * datos	= game->game_get_datos();
	Zonas_Manager* zonas = datos->get_zonas_manager();
	Zona** todas_las_zonas = zonas->get_zonas();
*/
	_puertas_pincho[0] = new Puerta_Pincho(0,12.5*mult,0,23.5*mult, _todas_las_zonas[0], _todas_las_zonas[2],6);	//Entre la sala 1 y 7
	_interruptores[0] = new Interruptor(0,6*mult,0,19*mult,_puertas_pincho[0],false,false, 500);
	_interruptores[1] = new Interruptor(0,8*mult,0,28*mult,_puertas_pincho[0],false,false, 500);


	//CUIDADO CON COMENTAR LAS ZONAS PUEDE HABER CORE DUMPED
	_puertas_pincho[1] = new Puerta_Pincho(0,10.5*mult,0,45.5*mult, _todas_las_zonas[2], _todas_las_zonas[3],9);	//Entre la sala 7 y 10
	_interruptores[2] = new Interruptor(0,12.5*mult,0,48.5*mult,_puertas_pincho[1],false,false, 500);
	_interruptores[3] = new Interruptor(0,12.5*mult,0,42.5*mult,_puertas_pincho[1],false,false, 500);


	_puertas_pincho[2] = new Puerta_Pincho(0,25.5*mult,0,17.5*mult, _todas_las_zonas[0], _todas_las_zonas[1],2);	//Entre la sala 1 y 3
	_interruptores[4] = new Interruptor(0,20*mult,0,11.5*mult,_puertas_pincho[2],false,false, 500);
	_interruptores[5] = new Interruptor(0,30*mult,0,21.5*mult,_puertas_pincho[2],false,false, 500);


// CAMBIAR EL PARAMETRO DE _TODAS_LAS_ZONAS
	_puertas_pincho[3] = new Puerta_Pincho(0,14.5*mult,0,71*mult, _todas_las_zonas[0], _todas_las_zonas[1],15);	//Entre la sala 10 y 16
	_interruptores[6] = new Interruptor(0,17*mult,0,63.5*mult,_puertas_pincho[3],false,false, 500);
	_interruptores[7] = new Interruptor(0,22.5*mult,0,71.5*mult,_puertas_pincho[3],false,false, 500);

	_puertas_pincho[4] = new Puerta_Pincho(0,41.5*mult,0,90.5*mult, _todas_las_zonas[0], _todas_las_zonas[1],21);	//Entre la sala 22 y 16
	_interruptores[8] = new Interruptor(0,46.5*mult,0,83.5*mult,_puertas_pincho[4],false,false, 500);
	_interruptores[9] = new Interruptor(0,33.5*mult,0,96.5*mult,_puertas_pincho[4],false,false, 500);


//	_interruptores[9] = new Interruptor(0,47.5*mult,0,98.5*mult,_puertas_pincho[4],false,false, 500);

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


    for(_cont = 0; _cont < _n_puertas_pincho; _cont++) {
		delete _puertas_pincho[_cont];
	}
	delete [] _puertas_pincho;

    for(_cont = 0; _cont < _n_interruptores; _cont++) {
		delete _interruptores[_cont];
	}
	delete [] _interruptores;

}


void Interactuable_Manager::update_interruptores(){

	for(unsigned short cont=0; cont<_n_puertas_pincho; cont++){
		_puertas_pincho[cont]->update();
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

