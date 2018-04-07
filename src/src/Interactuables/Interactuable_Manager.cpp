#include "Interactuable_Manager.h"

#include "Llave.h"
#include "Puerta.h"
#include "Interruptor.h"
#include "Puerta_Pincho.h"

#include "../Zona.h"
#include "../Zonas_Manager.h"

#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Interfaz/Motor.h"


Interactuable_Manager::Interactuable_Manager(Zona** _todas_las_zonas) {
    
	// tener xml con la informacion de todos los objetos
    
	_n_llaves = 2;
	_n_puertas = 2;
	_n_puertas_pincho = 15;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
	_puertas_pincho = new Puerta_Pincho*[_n_puertas_pincho];
    
    unsigned short _cont;

	float mult = 4.9212625;
          
    _puertas[0] = new Puerta(1,31.35*mult,0*mult, 36.5*mult, 0, false, 4);			//puerta situada entre nodo 3 y 5 pasillo 4
    _puertas[1] = new Puerta(2,12.5*mult,0*mult, 21.155*mult, 0, false, 6); 		// puerta situada entre nodo 1 y nodo 7 pasillo 6

	
	_llaves[0] = new Llave(0, 35*mult, 0*mult, 55*mult,_puertas[0]->get_id());	//Lave situada en nodo 18, abre la puerta situada en pasillo 4
	_llaves[1] = new Llave(0, 12.5*mult, 0*mult, 17*mult,_puertas[1]->get_id());  // Llave situada en el nodo 1, abre puerta de pasillo 6





	_puertas_pincho[0] = new Puerta_Pincho(0,12.5*mult,0,23.5*mult, false, false, 0, _todas_las_zonas[0], _todas_las_zonas[2],6);	//Entre la sala 1 y 7

	_puertas_pincho[1] = new Puerta_Pincho(0,10.5*mult,0,45.5*mult, false, false, 0, _todas_las_zonas[2], _todas_las_zonas[3],9);	//Entre la sala 7 y 10
	

	_puertas_pincho[2] = new Puerta_Pincho(0,25.5*mult,0,17.5*mult, true, false, 0, _todas_las_zonas[0], _todas_las_zonas[1],2);	//Entre la sala 1 y 3
	_interrutoress.push_back(new Interruptor(0,30*mult,0,21.2*mult,90, _puertas_pincho[2],false,false, 500));

	_puertas_pincho[3] = new Puerta_Pincho(1,18*mult,0*mult, 31.5*mult, true, true, 90, _todas_las_zonas[0], _todas_las_zonas[1],8);	//Entre la sala 3 y 7


	_puertas_pincho[4] = new Puerta_Pincho(0,20*mult,0,73.5*mult, false, false, 90, _todas_las_zonas[3], _todas_las_zonas[5],15);	//Entre la sala 10 y 16

	_puertas_pincho[5] = new Puerta_Pincho(0,41.5*mult,0,87.5*mult, false, true, 0, _todas_las_zonas[5], _todas_las_zonas[4],21);	//Entre la sala 22 y 16
	_puertas_pincho[6] = new Puerta_Pincho(0,25.5*mult,0,85.5*mult, false, false, 0, _todas_las_zonas[3], _todas_las_zonas[5],20);	//Entre la sala 10 y 16

	_puertas_pincho[7] = new Puerta_Pincho(0,25.5*mult,0,62*mult, false, false, 0, _todas_las_zonas[5],nullptr,17); //Entre la sala 16 
	_puertas_pincho[8] = new Puerta_Pincho(0,45.5*mult,0,62*mult, false, false, 0, _todas_las_zonas[5],nullptr,17); //Entre la sala 16 

 
	_puertas_pincho[9] =  new Puerta_Pincho(0, 78.55*mult, 0, 57.5*mult, true, true, 0, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)
	_puertas_pincho[10] = new Puerta_Pincho(0, 78.45*mult, 0, 59.3*mult, true, true, 180, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)
	_puertas_pincho[11] = new Puerta_Pincho(0, 78.52*mult, 0, 61.1*mult, true, true, 0, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)
	_puertas_pincho[12] = new Puerta_Pincho(0, 78.57*mult, 0, 62.9*mult, true, true, 180, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)
	_puertas_pincho[13] = new Puerta_Pincho(0, 78.5*mult, 0, 64.7*mult, true, true, 0, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)
	_puertas_pincho[14] = new Puerta_Pincho(0, 78.53*mult, 0, 66.5*mult, true, true, 180, nullptr, nullptr, 31); //Entre la sala 30 y 32 (pasillo 31)


	_interrutoress.push_back(new Interruptor(0,33.5*mult,0,96.5*mult,0, _puertas_pincho[5],false,false, 500));
	_interrutoress.push_back(new Interruptor(0,45*mult,0,40*mult,0, _puertas_pincho[5],false,false, 500));


	// ESTE TIPO DE PUERTAS NO ESTAN HECHAS :)
	_interrutoress.push_back(new Interruptor(0, 80.5*mult, 0, 67.8*mult, 180,  _puertas_pincho[12], false, false, 500));
	_interrutoress.push_back(new Interruptor(0, 80.5*mult, 0, 71*mult, 0,  _puertas_pincho[13], false, false, 500));
	_interrutoress.push_back(new Interruptor(0, 80.5*mult, 0, 74.2*mult, 180,  _puertas_pincho[14], false, false, 500));
	_interrutoress.push_back(new Interruptor(0, 75.5*mult, 0, 67.8*mult, 0,  _puertas_pincho[9], false, false, 500));
	_interrutoress.push_back(new Interruptor(0, 75.5*mult, 0, 71*mult, 180,  _puertas_pincho[10], false, false, 500));
	_interrutoress.push_back(new Interruptor(0, 75.5*mult, 0, 74.2*mult, 0,  _puertas_pincho[11], false, false, 500));

	//Zona 7
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[0]);
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[1]);
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[3]);


	//Zona 16
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[4]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[5]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[6]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[7]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[8]);
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

	
    for(_cont = 0; _cont < _interrutoress.size(); _cont++) {
		delete _interrutoress[_cont];
	}
	_interrutoress.clear();

}


void Interactuable_Manager::update_interruptores(){
	uint8_t _n_interruptores = _interrutoress.size();
	for(unsigned short cont=0; cont<_n_interruptores; cont++){
		_interrutoress[cont]->update();
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

std::vector<Interruptor*> Interactuable_Manager::get_interruptores(){
	return _interrutoress;
}

unsigned short Interactuable_Manager::get_n_llaves(){
	return _n_llaves;
}

unsigned short Interactuable_Manager::get_n_puertas(){
	return _n_puertas;
}

unsigned short Interactuable_Manager::get_n_puertas_pincho(){
	return _n_puertas_pincho;
}

