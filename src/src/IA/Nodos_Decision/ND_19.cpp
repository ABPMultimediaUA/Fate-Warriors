#include "ND_19.h"

#include "../Blackboard.h"

#include<iostream>

ND_19::ND_19(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_19::~ND_19() {

}

enum Enum_Acciones ND_19::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_19\n";
	if(_blackboard->_enemigo_mas_cerca_esta_cerca == true) { // TRUE, es 1
        //std::cout <<"hay enemigo cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}

    //std::cout <<"NO hay enemigo cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}
