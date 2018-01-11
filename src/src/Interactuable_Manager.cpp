#include "Interactuable_Manager.h"

//#include "Interfaz/Interfaz.h"

#include "Llave.h"
#include "Puerta.h"
#include "Interruptor.h"

Interactuable_Manager::Interactuable_Manager() {
    // tener xml con la informacion de todos los objetos
    
	_n_llaves = 1;
	_n_puertas = 1;

	_llaves = new Llave*[_n_llaves];
    _puertas = new Puerta*[_n_puertas];
    
    unsigned short _cont;

	//for(_cont = 0; _cont < _n_llaves; _cont++) {
		//_llaves[_cont] = new Llave(20,0,10,230,25);
	//}
	
	//for(_cont = 0; _cont < _n_puertas; _cont++) {
		//_puertas[_cont] = new Puerta(25,0,10,-180,false);
	//}

	float mult = 4.9212625;
    
    _llaves[0] = new Llave(0, 5*mult, 1*mult, 37*mult,1);
    //_llaves[1] = new Llave(0,10*mult,1*mult,10*mult,1);
    
    _puertas[0] = new Puerta(1,18*mult,1*mult, 31.5*mult,false);
    //_puertas[1] = new Puerta(127,-0,0,-180,false);
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
