#include "Zonas_Manager.h"
#include "Zona.h"
#include <iostream>

Zonas_Manager::Zonas_Manager() {
    // tener xml con la informacion de todos los objetos
    
	_n_zonas = 4;
	_zonas = new Zona*[_n_zonas];

    unsigned short _cont;
	float mult = 4.9212625;
//	_zonas[0] = new Zona(5*mult, 0*mult, 37*mult,20,20, Enum_Equipo_A);

	_zonas[0]  = new Zona(5*2.5*mult, 0*mult, 5*2.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_A); //Zona 1	
	_zonas[1]  = new Zona(29.5*mult, 0*mult, 28.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_B); //Zona 3
	_zonas[2]  = new Zona(10.5*mult, 0*mult, 34.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_B);		//Zona 7
	_zonas[3]  = new Zona(10.5*mult, 0*mult, 56.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_B);   //Zona 10


	/*
	_zonas[2]  = new Zona(38*mult, 0*mult, 35*mult,8*mult,10*mult, Enum_Equipo_B);
	_zonas[3]  = new Zona(3*mult, 0*mult, 27*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[4]  = new Zona(3*mult, 0*mult, 49*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[5]  = new Zona(3*mult, 0*mult, 82*mult,9*mult,10*mult, Enum_Equipo_A);   //NEUTRO
	_zonas[6]  = new Zona(11*mult, 0*mult, 101*mult,6*mult,10*mult, Enum_Equipo_A); //NEUTRO
	_zonas[7]  = new Zona(22*mult, 0*mult, 64*mult,25*mult,20*mult, Enum_Equipo_B);
	_zonas[8]  = new Zona(30*mult, 0*mult, 51*mult,10*mult,8*mult, Enum_Equipo_A); //NEUTRO
	_zonas[9]  = new Zona(28*mult, 0*mult, 97*mult,20*mult,15*mult, Enum_Equipo_B);
	_zonas[10]  = new Zona(54*mult, 0*mult, 47*mult,7*mult,9*mult, Enum_Equipo_A); //NEUTRO
	_zonas[11]  = new Zona(54*mult, 0*mult, 70*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[12]  = new Zona(66*mult, 0*mult, 89*mult,15*mult,20*mult, Enum_Equipo_B);
	_zonas[13]  = new Zona(75*mult, 0*mult, 67*mult,6*mult,8*mult, Enum_Equipo_A); //NEUTRO
	_zonas[14]  = new Zona(59*mult, 0*mult, 27*mult,35*mult,35*mult, Enum_Equipo_B);
	*/

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