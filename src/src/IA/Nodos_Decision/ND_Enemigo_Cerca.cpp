#include "ND_Enemigo_Cerca.h"

#include "../Blackboard.h"

#include<iostream>

ND_Enemigo_Cerca::ND_Enemigo_Cerca(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Enemigo_Cerca::~ND_Enemigo_Cerca() {

}

enum Enum_Acciones ND_Enemigo_Cerca::toma_decision(Blackboard* _blackboard){

	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_blackboard->_enemigo_mas_cerca_menos_de_30_metros == true) { // TRUE, es 1
		//std::cout <<"Enemigo cerca \n";
		return _nodo_der->toma_decision(_blackboard);
	}
	//std::cout <<"Enemigo lejos \n";
	return _nodo_izq->toma_decision(_blackboard);
}
