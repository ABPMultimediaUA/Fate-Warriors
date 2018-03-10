#include "ND_13.h"

#include "../Blackboard.h"

#include<iostream>

ND_13::ND_13(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_13::~ND_13() {

}

enum Enum_Acciones ND_13::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_13\n";
	if( _blackboard->_objeto_mas_cerca_esta_cerca == true && _blackboard->_habilidad_coger_objeto == true) { // TRUE, es 1
        //std::cout <<"_objeto_mas_cerca_esta_cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    //std::cout <<"NO _objeto_mas_cerca_esta_cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}