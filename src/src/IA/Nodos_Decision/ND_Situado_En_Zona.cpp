#include "ND_Situado_En_Zona.h"

#include "../Blackboard.h"
#include "../../Zona.h"

#include<iostream>

ND_Situado_En_Zona::ND_Situado_En_Zona(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Situado_En_Zona::~ND_Situado_En_Zona() {

}

enum Enum_Acciones ND_Situado_En_Zona::toma_decision(Blackboard* _blackboard){

	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_blackboard->_zona_actual == nullptr) { // TRUE, es 1
		return _nodo_der->toma_decision(_blackboard);
	}
	return _nodo_izq->toma_decision(_blackboard);
}
