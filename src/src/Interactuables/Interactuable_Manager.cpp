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
    
	_n_llaves = 1;
	_n_puertas = 1;
	_n_puertas_pincho = 8;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
	_puertas_pincho = new Puerta_Pincho*[_n_puertas_pincho];
    
    unsigned short _cont;

	float mult = 4.9212625;


	_puertas[0] = new Puerta(3, 77.5*mult,0*mult, 88.75*mult, 180, false, 6); 		// puerta situada entre nodo 1 y nodo 7 pasillo 6

	_llaves[0] = new Llave(3, 368, 0*mult, 450,_puertas[0]->get_id());  // Llave situada en el nodo 1, abre puerta de pasillo 6

	// ------------------------------------ PUERTAS PINCHO ------------------------------------


	// PUERTA TIEMPO/1 USO ENTRE SALAS 16 Y 22
	_puertas_pincho[0] = new Puerta_Pincho(0,365,0,534, true, 0, 21);	//Entre la sala 16 y 22


	// PUERTAS PINCHOS DE LA ZONA FINAL
	_puertas_pincho[1] =  new Puerta_Pincho(0, 78.55*mult, 0, 57.5*mult, true, 0, 31);
	_puertas_pincho[2] = new Puerta_Pincho(0, 78.45*mult, 0, 59.3*mult, true, 180, 31);
	_puertas_pincho[3] = new Puerta_Pincho(0, 78.52*mult, 0, 61.1*mult, true, 0, 31);
	_puertas_pincho[4] = new Puerta_Pincho(0, 78.57*mult, 0, 62.9*mult, true, 180, 31);
	_puertas_pincho[5] = new Puerta_Pincho(0, 78.5*mult, 0, 64.7*mult, true, 0, 31);
	_puertas_pincho[6] = new Puerta_Pincho(0, 78.53*mult, 0, 66.5*mult, true, 180, 31);


	// INTERRUPTOR DE UN SOLO USO EN ZONA 22
	_interrutores.push_back(new Interruptor_Un_Uso(0,376, 534, 90, 270, 90, 20));
	_interrutores[0]->agregar_puerta(_puertas_pincho[0]);


	// INTERRUPTOR TIEMPO EN ZONA 5
	_interrutores.push_back(new Interruptor_Tiempo(0, 355, 534, 270, 20000, 270, 90, 20));
	_interrutores[1]->agregar_puerta(_puertas_pincho[0]);


	// INTERRUPTORES DE ZONA FINAL
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 67.8*mult, 180, 90, 90, 20));	// 3
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 71*mult, 0, 90, 90, 20));		// 2
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 74.2*mult, 180, 90, 90, 20));	// 1
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 67.8*mult, 0, 90, 90, 20));	// 6
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 71*mult, 180, 90, 90, 20));	// 5
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 74.2*mult, 0, 90, 90, 20));	// 4

	_interrutores[2]->agregar_puerta(_puertas_pincho[4]);
	_interrutores[3]->agregar_puerta(_puertas_pincho[5]);
	_interrutores[4]->agregar_puerta(_puertas_pincho[6]);
	_interrutores[5]->agregar_puerta(_puertas_pincho[1]);
	_interrutores[6]->agregar_puerta(_puertas_pincho[2]);
	_interrutores[7]->agregar_puerta(_puertas_pincho[3]);

	_interrutores[4]->agregar_interruptor(_interrutores[6]);

	_interrutores[3]->agregar_interruptor(_interrutores[7]);
	_interrutores[3]->agregar_interruptor(_interrutores[5]);

	_interrutores[2]->agregar_interruptor(_interrutores[3]);

	_interrutores[7]->agregar_interruptor(_interrutores[6]);

	_interrutores[6]->agregar_interruptor(_interrutores[2]);

	_interrutores[5]->agregar_interruptor(_interrutores[2]);

	// ZONA COLISEO 28
	_puertas_pincho[7] = new Puerta_Pincho(0, 65*mult, 0, 101.5*mult, true, 270, 27);

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

