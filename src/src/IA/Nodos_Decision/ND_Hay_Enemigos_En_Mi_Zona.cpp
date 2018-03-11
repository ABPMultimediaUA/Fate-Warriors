#include "ND_Hay_Enemigos_En_Mi_Zona.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_Hay_Enemigos_En_Mi_Zona::ND_Hay_Enemigos_En_Mi_Zona(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Hay_Enemigos_En_Mi_Zona::~ND_Hay_Enemigos_En_Mi_Zona() {

}

enum Enum_Acciones ND_Hay_Enemigos_En_Mi_Zona::toma_decision(Blackboard* _blackboard){

    int num_enemigos_en_mi_zona;

    

    if(_blackboard->_npc_padre->get_equipo() == Enum_Equipo_A){
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_B;
    }
    else{
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_A;
    }
	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(num_enemigos_en_mi_zona > 0) { // TRUE, es 1
        std::cout <<"SI enemigos en mi zona \n";
        _blackboard->objetivo_x = _blackboard->_enemigo_mas_cerca->getX();
        _blackboard->objetivo_y = _blackboard->_enemigo_mas_cerca->getZ();
		return _nodo_der->toma_decision(_blackboard);
	}
    std::cout <<"NO enemigos en mi zona \n";
    //_blackboard->objetivo_x = _blackboard->_zona_enemiga_mas_cerca->getX();
    //_blackboard->objetivo_y = _blackboard->_zona_enemiga_mas_cerca->getZ();
	return _nodo_izq->toma_decision(_blackboard);
}
