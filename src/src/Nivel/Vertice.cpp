#include "Vertice.h"
//#include "Arista.h"
#include <iostream>
Vertice::Vertice(int _i_id){
	_id=_i_id;
	_sig = nullptr;
	_ady = nullptr;
}

Vertice::~Vertice(){
	//std::cout<< sig->id <<"         AAAAElija una opcion validaaaaaaaaaaaaaaaaa2"<<std::endl;
/*if(sig!=nullptr){
	std::cout<< sig->nombre <<"         AAAAElija una opcion validaaaaaaaaaaaaaaaaa2"<<std::endl;
	delete sig;
	sig=nullptr;
}
if(ady!=nullptr){
	delete ady;
	ady=nullptr;
}*/
}