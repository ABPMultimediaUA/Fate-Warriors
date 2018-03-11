#include "ND_7.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_7::ND_7(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_7::~ND_7() {

}

enum Enum_Acciones ND_7::toma_decision(Blackboard* _blackboard){
    Zona * zona_mas_cerca = _blackboard->_zona_mas_cerca;
    //std::cout <<"Entra ND_7\n";
	if( zona_mas_cerca->get_equipo() != _blackboard->_npc_padre->get_equipo()) { // TRUE, es 1

        _blackboard->objetivo_x = zona_mas_cerca->getX();
        _blackboard->objetivo_y = zona_mas_cerca->getZ();
        //std::cout <<"zona mas cerca es ENEMIGA\n";
        // Andar
		return _nodo_der->toma_decision(_blackboard);
	}
    //std::cout <<"zona mas cerca es ALIADA\n";
	return _nodo_izq->toma_decision(_blackboard);
}