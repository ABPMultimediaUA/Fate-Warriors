#include "Vertice.h"
//#include "Arista.h"
#include <iostream>
Vertice::Vertice(int _i_id,float _i_posx, float _i_posy, Grafo *_i_grafo_lod1):
_id(_i_id), _posx(_i_posx), _posy(_i_posy), _lod1(_i_grafo_lod1), _sig(nullptr),
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