#include "ND_4.h"

#include "../Blackboard.h"
#include "../../Zona.h"

#include<iostream>

ND_4::ND_4(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_4::~ND_4() {

}

enum Enum_Acciones ND_4::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_4\n";
	if( _blackboard->_objeto_mas_cerca_esta_cerca == true && _blackboard->_habilidad_coger_objeto == true) { // TRUE, es 1
        //std::cout <<"_objeto_mas_cerca_esta_cerca\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    _blackboard->objetivo_x = _blackboard->_zona_enemiga_mas_cerca->getX();
    _blackboard->objetivo_y = _blackboard->_zona_enemiga_mas_cerca->getZ();
    //Andar
    //std::cout <<"NO _objeto_mas_cerca_esta_cerca\n";
	return _nodo_izq->toma_decision(_blackboard);
}