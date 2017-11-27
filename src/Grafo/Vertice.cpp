#include "Vertice.h"
#include "Arista.h"
#include <iostream>
Vertice::Vertice(){
	sig = nullptr;
	ady = nullptr;
}

Vertice::~Vertice(){
if(sig!=nullptr){
	std::cout<< sig->nombre <<"         AAAAElija una opcion validaaaaaaaaaaaaaaaaa2"<<std::endl;
	delete sig;
	sig=nullptr;
}
if(ady!=nullptr){
	delete ady;
	ady=nullptr;
}
}