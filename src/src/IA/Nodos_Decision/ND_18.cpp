#include "ND_18.h"

#include "../Blackboard.h"

#include<iostream>

ND_18::ND_18(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_18::~ND_18() {

}

enum Enum_Acciones ND_18::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_18\n";
	if(_blackboard->_objeto_mas_cerca_que_enemigo_mas_cerca == true) { // TRUE, es 1
        std::cout <<"hay _objeto_mas_cerca_que_enemigo_mas_cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}

    std::cout <<"NO hay_objeto_mas_cerca_que_enemigo_mas_cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}
