#include "ND_12.h"

#include "../Blackboard.h"
#include "../../Personajes/Character.h"

#include<iostream>

ND_12::ND_12(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_12::~ND_12() {

}

enum Enum_Acciones ND_12::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_12\n";
	if( _blackboard->_enemigo_mas_cerca->get_accion() == Accion_pre_atacar) { // TRUE, es 1
        //std::cout <<"enemigo Accion_pre_atacar\n";
		return _nodo_der->toma_decision(_blackboard);
	}
	
    //std::cout <<"NO enemigo Accion_pre_atacar\n";
	return _nodo_izq->toma_decision(_blackboard);
}
