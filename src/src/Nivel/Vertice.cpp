#include "Vertice.h"
#include "Arista.h"
#include "Nodo.h"
#include "Grafo.h"
#include <iostream>

Vertice::Vertice(float _i_posx, float _i_posy,float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1):
_id(_i_id), _posx(_i_posx), _posy(_i_posy), _lod1(_i_grafo_lod1),_lod(4) , _sig(nullptr),
_ady(nullptr),_n_enemigos(0), _ancho(_i_ancho), _alto(_i_alto){

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
	if(Nodo * n = dynamic_cast<Nodo*>(this)){
		n->_blackboard->set_lod(_i_cont);
	}
	_lod=_i_cont;
	Arista* _ArisAux = _ady;
	while(_ArisAux != nullptr){//recorrer nivel 1
		if(_ArisAux->_ady->_lod>_i_cont){
			
			_ArisAux->_ady->set_lod(_i_cont+1);
		}
		
		_ArisAux = _ArisAux->_sig;
	}
}
bool Vertice::pos2id(float _i_x, float _i_y){
	if(_posx<_i_x && (_posx+_ancho)>_i_x && _posy<_i_y && (_posy+_alto)>_i_y){
		return true;
	}else{
		return false;
	}
}