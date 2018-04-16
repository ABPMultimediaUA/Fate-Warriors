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
    
	_n_llaves = 3;
	_n_puertas = 3;
	_n_puertas_pincho = 18;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
	_puertas_pincho = new Puerta_Pincho*[_n_puertas_pincho];
    
    unsigned short _cont;

	float mult = 4.9212625;
          
    _puertas[0] = new Puerta(1,31.35*mult,0*mult, 36.5*mult, 0, false, 4);			//puerta situada entre nodo 3 y 5 pasillo 4
    _puertas[1] = new Puerta(2,12.5*mult,0*mult, 21.155*mult, 0, false, 6); 		// puerta situada entre nodo 1 y nodo 7 pasillo 6
	_puertas[2] = new Puerta(3, 77.5*mult,0*mult, 88.75*mult, 0, false, 6); 		// puerta situada entre nodo 1 y nodo 7 pasillo 6

	
	_llaves[0] = new Llave(0, 35*mult, 0*mult, 55*mult,_puertas[0]->get_id());	//Lave situada en nodo 18, abre la puerta situada en pasillo 4
	_llaves[1] = new Llave(1, 12.5*mult, 0*mult, 17*mult,_puertas[1]->get_id());  // Llave situada en el nodo 1, abre puerta de pasillo 6
	_llaves[2] = new Llave(3, 14*mult, 0*mult, 102*mult,_puertas[2]->get_id());  // Llave situada en el nodo 1, abre puerta de pasillo 6




	// ------------------------------------ PUERTAS PINCHO ------------------------------------

	// ZONA COLISEO 7
	_puertas_pincho[0] = new Puerta_Pincho(0, 12.5*mult, 0, 23.5*mult, false, 0, 6);		//Entre la sala 1 y 7
	_puertas_pincho[3] = new Puerta_Pincho(1, 18*mult, 0*mult, 31.5*mult, false, 90, 8);	//Entre la sala 3 y 7
	_puertas_pincho[1] = new Puerta_Pincho(0, 10.5*mult, 0, 45.5*mult, false, 0, 9);		//Entre la sala 7 y 10
	

	// PUERTA 1 SOLO USO ENTRE SALAS 1 Y 3
	_puertas_pincho[2] = new Puerta_Pincho(0,25.5*mult,0,17.5*mult, true, 0, 2);	//Entre la sala 1 y 3


	// PUERTA TIEMPO/1 USO ENTRE SALAS 16 Y 22
	_puertas_pincho[5] = new Puerta_Pincho(0,41.45*mult,0,87.5*mult, true, 0, 21);	//Entre la sala 16 y 22


	// ZONA COLISEO 16
	_puertas_pincho[4] = new Puerta_Pincho(0,20*mult,0,73.5*mult, false, 90, 15);	//Entre la sala 10 y 16
	_puertas_pincho[6] = new Puerta_Pincho(0,25.5*mult,0,85.5*mult, false, 0, 20);	//Entre la sala 10 y 16
	_puertas_pincho[7] = new Puerta_Pincho(0,25.5*mult,0,62*mult, false, 0, 17); 	//Entre la sala 16 
	_puertas_pincho[8] = new Puerta_Pincho(0,45.5*mult,0,62*mult, false, 0, 17); 	//Entre la sala 16 


	// PUERTAS PINCHOS DE LA ZONA FINAL
	_puertas_pincho[9] =  new Puerta_Pincho(0, 78.55*mult, 0, 57.5*mult, true, 0, 31);
	_puertas_pincho[10] = new Puerta_Pincho(0, 78.45*mult, 0, 59.3*mult, true, 180, 31);
	_puertas_pincho[11] = new Puerta_Pincho(0, 78.52*mult, 0, 61.1*mult, true, 0, 31);
	_puertas_pincho[12] = new Puerta_Pincho(0, 78.57*mult, 0, 62.9*mult, true, 180, 31);
	_puertas_pincho[13] = new Puerta_Pincho(0, 78.5*mult, 0, 64.7*mult, true, 0, 31);
	_puertas_pincho[14] = new Puerta_Pincho(0, 78.53*mult, 0, 66.5*mult, true, 180, 31);


	// PUERA 1 SOLO USO ENTRE SALAS 14 Y 16
	_puertas_pincho[15] = new Puerta_Pincho(0, 6.5*mult, 0, 92.5*mult, true, 180, 13);


	// ZONA COLISEO 28
	_puertas_pincho[16] = new Puerta_Pincho(0, 65*mult, 0, 101.5*mult, false, 270, 27);


	// ZONA COLISEO 26
	_puertas_pincho[17] = new Puerta_Pincho(0, 57.45*mult, 0, 86.5*mult, false, 180, 25);


	// ------------------------------------ INTERRUPTORES ------------------------------------
 
	// INTERRUPTOR DE UN SOLO USO EN ZONA 3
	_interrutores.push_back(new Interruptor_Un_Uso(0, 29*mult, 21.4*mult, 90, 90, 90, 20));
	_interrutores[0]->agregar_puerta(_puertas_pincho[2]);


	// INTERRUPTOR DE UN SOLO USO EN ZONA 22
	_interrutores.push_back(new Interruptor_Un_Uso(0, 47.25*mult, 97.5*mult, 90, 90, 90, 20));
	_interrutores[1]->agregar_puerta(_puertas_pincho[5]);


	// INTERRUPTOR TIEMPO EN ZONA 5
	_interrutores.push_back(new Interruptor_Tiempo(0, 42*mult, 44.75*mult, 270, 17000, 90, 90, 20));
	_interrutores[2]->agregar_puerta(_puertas_pincho[5]);
	_interrutores[2]->agregar_puerta(_puertas_pincho[3]);


	// INTERRUPTORES DE ZONA FINAL
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 67.8*mult, 180, 90, 90, 20));	// 3
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 71*mult, 0, 90, 90, 20));		// 2
	_interrutores.push_back(new Interruptor_Propagador(0, 80.5*mult, 74.2*mult, 180, 90, 90, 20));	// 1
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 67.8*mult, 0, 90, 90, 20));	// 6
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 71*mult, 180, 90, 90, 20));	// 5
	_interrutores.push_back(new Interruptor_Propagador(0, 75.5*mult, 74.2*mult, 0, 90, 90, 20));	// 4

	_interrutores[3]->agregar_puerta(_puertas_pincho[12]);
	_interrutores[4]->agregar_puerta(_puertas_pincho[13]);
	_interrutores[5]->agregar_puerta(_puertas_pincho[14]);
	_interrutores[6]->agregar_puerta(_puertas_pincho[9]);
	_interrutores[7]->agregar_puerta(_puertas_pincho[10]);
	_interrutores[8]->agregar_puerta(_puertas_pincho[11]);

	_interrutores[5]->agregar_interruptor(_interrutores[7]);

	_interrutores[4]->agregar_interruptor(_interrutores[8]);
	_interrutores[4]->agregar_interruptor(_interrutores[6]);

	_interrutores[3]->agregar_interruptor(_interrutores[4]);

	_interrutores[8]->agregar_interruptor(_interrutores[7]);

	_interrutores[7]->agregar_interruptor(_interrutores[3]);

	_interrutores[6]->agregar_interruptor(_interrutores[3]);


	// INTERRUPTOR 1 USO EN ZONA 26
	_interrutores.push_back(new Interruptor_Un_Uso(0, 61.5*mult, 70.5*mult, 90, 90, 90, 20));
	_interrutores[9]->agregar_puerta(_puertas_pincho[15]);




	// Zona 7
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[0]);
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[1]);
	_todas_las_zonas[2]->set_puerta_pincho_asociada(_puertas_pincho[3]);


	// Zona 16
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[4]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[6]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[7]);
	_todas_las_zonas[5]->set_puerta_pincho_asociada(_puertas_pincho[8]);


	// Zona 28
	_todas_las_zonas[7]->set_puerta_pincho_asociada(_puertas_pincho[16]);


	// Zona 26
	_todas_las_zonas[8]->set_puerta_pincho_asociada(_puertas_pincho[17]);
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

