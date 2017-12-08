#include "Vertice.h"
#include "Arista.h"
#include "Grafo.h"
#include <iostream>

Vertice::Vertice(float _i_posx, float _i_posy, int _i_id, Grafo *_i_grafo_lod1):
_id(_i_id), _posx(_i_posx), _posy(_i_posy), _lod1(_i_grafo_lod1),_lod(4) , _sig(nullptr),
_ady(nullptr){

}

Vertice::~Vertice(){
	delete _lod1;
	_sig = nullptr;
	_ady = nullptr;
	_lod1 = nullptr; //grafo level of detail
}
Grafo *Vertice::get_lod1(){
	return _lod1;
}

float Vertice::get_coord_x(){
	return _posx;
}

float Vertice::get_coord_y(){
	return _posy;
}
void Vertice::set_lod(unsigned short _i_cont){
	if(_i_cont>4){
		_i_cont=4;
	}
	_lod=_i_cont;
	std::cout<< _id << std::endl;
	Arista* _ArisAux = _ady;
	while(_ArisAux != nullptr){//recorrer nivel 1
		if(_ArisAux->_ady->_lod>_i_cont){
			
			_ArisAux->_ady->set_lod(_i_cont+1);
		}
		
		_ArisAux = _ArisAux->_sig;
	}
}