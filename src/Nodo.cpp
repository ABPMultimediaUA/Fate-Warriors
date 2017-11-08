/*
 * Nodo.cpp
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */

#include "Nodo.h"

Nodo::Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto) {
	// TODO Auto-generated constructor stub
	this->_nodo_x=_i_x;
	this->_nodo_y=_i_y;
	this->_nodo_ancho=_i_ancho;
	this->_nodo_alto=_i_alto;
}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}
void Nodo::nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto){
	Objeto* _objeto=new Objeto(_i_x, _i_y, _i_ancho, _i_alto);
	_objetos.push_back(_objeto);
	delete _objeto;
}


