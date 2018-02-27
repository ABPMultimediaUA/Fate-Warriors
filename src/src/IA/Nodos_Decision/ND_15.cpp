#include "ND_15.h"

#include "../Blackboard.h"

#include<iostream>

ND_15::ND_15(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_15::~ND_15() {

}

enum Enum_Acciones ND_15::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_15\n";
	if(_blackboard->_enemigo_mas_cerca_esta_muy_cerca == true) { // TRUE, es 1
        //std::cout <<"_enemigo_mas_cerca_esta_muy_cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}

    //std::cout <<"_enemigo_mas_cerca_ NO esta_muy_cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}
