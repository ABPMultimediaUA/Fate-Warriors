#include "Zonas_Manager.h"

#include "Zona.h"
#include "Zona_Final.h"
#include "Zona_Inicial.h"
#include "Zona_Coliseo.h"
#include "Zona_Respawn_Infinito.h"

#include <iostream>

Zonas_Manager::Zonas_Manager() {

	_equipoA = 0;
	_equipoB = 0;


    // tener xml con la informacion de todos los objetos
    
	_n_zonas = 10;
	_zonas = new Zona*[_n_zonas];

    unsigned short _cont;
	float mult = 4.9212625;
//	_zonas[0] = new Zona(5*mult, 0*mult, 37*mult,20,20, Enum_Equipo_A);

	_zona_incial = new Zona_Inicial(12.5*mult, 0*mult, 12.5*mult,(15*mult)/2,(15*mult)/2, 12.5*mult, 11*mult); 	//Zona 1
	_zonas[0] = _zona_incial;
		
	
	_zonas[1]  = new Zona_Respawn_Infinito(29.5*mult, 0*mult, 28.5*mult,(15*mult)/2,(15*mult)/2, 5, 120); 		//Zona 3
	
	_zonas[2]  = new Zona_Coliseo(10.5*mult, 0*mult, 34.5*mult, (15*mult)/2, (15*mult)/2, 1, 2, 1, 3, 11);		//Zona 7
		
	_zonas[3]  = new Zona_Respawn_Infinito(10.5*mult, 0*mult, 56.5*mult,(15*mult)/2,(15*mult)/2, 4, 125);   	//Zona 10
	
	_zonas[4]  = new Zona_Respawn_Infinito(38*mult, 0*mult, 104.5*mult,(20*mult)/2,(15*mult)/2, 7, 17*mult);	// Zona 22
		
	_zonas[5]  = new Zona_Coliseo(34.5*mult, 0*mult, 74*mult, (25*mult)/2, (20*mult)/2, 2, 4, 1, 4, 6);			// Zona 16
	
	_zonas[6]  = new Zona_Final(72*mult, 0*mult, 42*mult,(25*mult)/2,(30*mult)/2, 6, 5, 2, 8);						// Zona 32

	_zonas[7]   = new Zona_Coliseo(73.5*mult, 0*mult, 99*mult, (15*mult)/2, (20*mult)/2, 6, 4, 2, 2, 5);			// Zona 28

	_zonas[8]	= new Zona_Coliseo(61.5*mult, 0*mult, 77.5*mult, (15*mult)/2, (15*mult)/2, 2, 3, 3, 7, 5);			// Zona 26
	
	_zonas[9]	= new Zona_Respawn_Infinito(14*mult, 0*mult, 106*mult,(6*mult)/2,(10*mult)/2, 2, 65);
}

Zonas_Manager::~Zonas_Manager() {
    unsigned short _cont;
    
	for(_cont = 0; _cont < _n_zonas; _cont++) {
		delete _zonas[_cont];
	}
	delete [] _zonas;
}

void Zonas_Manager::actualizar_zonas(){

	for(uint8_t zona=0; zona<_n_zonas; zona++){
		_zonas[zona]->actualizar_zona();
	}
}

Zona** Zonas_Manager::get_zonas(){
	return _zonas;
}

unsigned short Zonas_Manager::get_n_zonas(){
	return _n_zonas;
}


Vector2 Zonas_Manager::get_posicion_zona_inicial(){
	return _zona_incial->get_posicion_inicial();
}