#include "ND_16.h"

#include "../Blackboard.h"
#include "../../Objeto.h"

#include<iostream>

ND_16::ND_16(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_16::~ND_16() {

}

enum Enum_Acciones ND_16::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_16\n";
	if(_blackboard->_objeto_mas_cerca_esta_muy_cerca == true) { // TRUE, es 1
        // Interactuar
        std::cout <<"_objeto_mas_cerca_esta_muy_cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    // Andar
    Objeto * obj = _blackboard->_objeto_mas_cerca;

    _blackboard->objetivo_x = obj->getX();
	_blackboard->objetivo_y = obj->getZ();
    std::cout <<"_objeto_mas_cerca NO _esta_muy_cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}
