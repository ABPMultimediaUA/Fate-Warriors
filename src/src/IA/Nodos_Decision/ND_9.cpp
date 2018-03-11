#include "ND_9.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_9::ND_9(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_9::~ND_9() {

}

enum Enum_Acciones ND_9::toma_decision(Blackboard* _blackboard){

    int num_enemigos_en_mi_zona;

    if(_blackboard->_npc_padre->get_equipo() == Enum_Equipo_A){
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_B;
    }
    else{
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_A;
    }

    //std::cout <<"Entra ND_9\n";
	if(num_enemigos_en_mi_zona > 0) { // TRUE, es 1
        //std::cout <<"en zona actual hay enemigos\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    //std::cout <<"en zona actual NO hay enemigos\n";
	return _nodo_izq->toma_decision(_blackboard);
}