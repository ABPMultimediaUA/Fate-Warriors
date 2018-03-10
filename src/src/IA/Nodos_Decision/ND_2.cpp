#include "ND_2.h"

#include "../Blackboard.h"
#include "../../Zona.h"

#include<iostream>

ND_2::ND_2(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_2::~ND_2() {

}

enum Enum_Acciones ND_2::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_2\n";
	if( _blackboard->_zona_mas_cerca->siendo_capturada() == true && _blackboard->_habilidad_defender == true) { // TRUE, es 1

        _blackboard->objetivo_x = _blackboard->_zona_mas_cerca->getX();
        _blackboard->objetivo_y = _blackboard->_zona_mas_cerca->getZ();
        //std::cout <<"zona mas cerca (aliada) siendo conquistada\n";
        // Andar
		return _nodo_der->toma_decision(_blackboard);
	}
    _blackboard->objetivo_x = _blackboard->_zona_enemiga_mas_cerca->getX();
    _blackboard->objetivo_y = _blackboard->_zona_enemiga_mas_cerca->getZ();
    //std::cout <<"zona mas cerca (aliada) NO siendo conquistada\n";
    // Andar
	return _nodo_izq->toma_decision(_blackboard);
}