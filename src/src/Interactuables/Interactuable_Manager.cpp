#include "Interactuable_Manager.h"

#include "Llave.h"
#include "Puerta.h"
#include "Puerta_Pincho.h"

#include "Interruptor.h"
#include "Interruptores/Interruptor_Propagador.h"
#include "Interruptores/Interruptor_Tiempo.h"
#include "Interruptores/Interruptor_Un_Uso.h"

#include "../Zonas/Zona.h"
#include "../Zonas/Zonas_Manager.h"

#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Interfaz/Motor.h"


Interactuable_Manager::Interactuable_Manager(Zona** _todas_las_zonas) {
    
	// tener xml con la informacion de todos los objetos
    
	_n_llaves = 0;
	_n_puertas = 0;
	_n_puertas_pincho = 4;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
	_puertas_pincho = new Puerta_Pincho*[_n_puertas_pincho];
    
    unsigned short _cont;

	float mult = 4.9212625;



	// ------------------------------------ PUERTAS PINCHO ------------------------------------

	// ZONA COLISEO 7
	_puertas_pincho[0] = new Puerta_Pincho(0, 12.5*mult, 0, 23.5*mult, false, 0, 6);		//Entre la sala 1 y 7
	_puertas_pincho[3] = new Puerta_Pincho(1, 18*mult, 0*mult, 31.5*mult, false, 90, 8);	//Entre la sala 3 y 7
	_puertas_pincho[1] = new Puerta_Pincho(0, 10.5*mult, 0, 45.5*mult, true, 0, 9);		//Entre la sala 7 y 10

	// PUERTA 1 SOLO USO ENTRE SALAS 1 Y 3
	_puertas_pincho[2] = new Puerta_Pincho(0,25.5*mult,0,17.5*mult, true, 0, 2);	//Entre la sala 1 y 3

	// Zona 7
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[0]);
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[3]);

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

	
    for(_cont = 0; _cont < _interrutores.size(); _cont++) {
		delete _interrutores[_cont];
	}
	_interrutores.clear();

}


void Interactuable_Manager::update_interruptores(){
	uint8_t _n_interruptores = _interrutores.size();
	for(unsigned short cont=0; cont<_n_interruptores; cont++){
		_interrutores[cont]->update();
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
	return _interrutores;
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

