#include "Vertice.h"
#include "Arista.h"
#include "Grafo.h"
#include <iostream>
Vertice::Vertice(){
	_sig = nullptr;
	_ady = nullptr;
	_lod1 = nullptr; //grafo level of detail
}

Vertice::~Vertice(){
	std::cout << "algo4" <<std::endl;
		delete _lod1;
	
	_sig = nullptr;
	_ady = nullptr;
	_lod1 = nullptr;
	std::cout << "algo5" <<std::endl;
}
Grafo *Vertice::get_lod1(){
	return _lod1;
}

int Vertice::get_coord_x(){
	return _posx;
}

int Vertice::get_coord_y(){
	return _posy;
}