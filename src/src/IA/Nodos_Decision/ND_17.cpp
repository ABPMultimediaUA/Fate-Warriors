#include "ND_17.h"

#include "../Blackboard.h"
#include "../../Zonas/Zona.h"
#include "../../Personajes/NPC.h"

//#include<iostream>

ND_17::ND_17(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_17::~ND_17() {

}

enum Enum_Acciones ND_17::toma_decision(Blackboard* _blackboard){

/*
	int num_aliados_en_mi_zona;

	if(_blackboard->_zona_actual != nullptr){
		
		if(_blackboard->_npc_padre->get_equipo() == Enum_Equipo_A){
			num_aliados_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_A;
		}
		else{
			num_aliados_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_B;
		}
	}
	*/
    //std::cout <<"Entra ND_17\n";
	if( _blackboard->_zona_actual != nullptr /*&& num_aliados_en_mi_zona < 3*/) { // TRUE, es 1
        //std::cout <<"estoy en una zona\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    //std::cout <<"NO estoy en una zona\n";
	return _nodo_izq->toma_decision(_blackboard);
}