#include "ND_14.h"

#include "../Blackboard.h"
#include "../../Zonas/Zona.h"
#include "../../Personajes/NPC.h"

//#include<iostream>

ND_14::ND_14(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_14::~ND_14() {

}

enum Enum_Acciones ND_14::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_14\n";
	if( _blackboard->_zona_actual->get_equipo() == _blackboard->_npc_padre->get_equipo()) { // TRUE, es 1
        //std::cout <<"zona actual es ALIADA\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    //std::cout <<"zona actual es ENEMIGA\n";
	return _nodo_izq->toma_decision(_blackboard);
}