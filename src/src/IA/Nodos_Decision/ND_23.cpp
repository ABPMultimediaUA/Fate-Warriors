#include "ND_23.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_23::ND_23(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_23::~ND_23() {

}

enum Enum_Acciones ND_23::toma_decision(Blackboard* _blackboard){

    int num_enemigos_en_mi_zona;
    int num_aliados_en_mi_zona;

    std::cout <<"23 \n";

    if(_blackboard->_npc_padre->get_equipo() == Enum_Equipo_A){
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_B;
        num_aliados_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_A;
    }
    else{
        num_enemigos_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_A;
        num_aliados_en_mi_zona = _blackboard->_zona_actual->_num_characters_equipo_B;
    }

    //std::cout <<"Entra ND 23\n";
	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(num_aliados_en_mi_zona - num_enemigos_en_mi_zona > -2) { // TRUE, es 1
        _blackboard->objetivo_x = _blackboard->_enemigo_mas_cerca->getX();
        _blackboard->objetivo_y = _blackboard->_enemigo_mas_cerca->getZ();
        std::cout <<"sigue enemigo mas cerca \n";
		return _nodo_der->toma_decision(_blackboard);
	}
 //   _blackboard->objetivo_x = _blackboard->_zona_enemiga_mas_cerca->getX();
  //  _blackboard->objetivo_y = _blackboard->_zona_enemiga_mas_cerca->getZ();
    std::cout <<"sigue zona enemiga mas cerca \n";
	return _nodo_izq->toma_decision(_blackboard);
}
