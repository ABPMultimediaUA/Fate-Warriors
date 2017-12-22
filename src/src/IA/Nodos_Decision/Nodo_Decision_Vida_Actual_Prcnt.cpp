#include "Nodo_Decision_Vida_Actual_Prcnt.h"

#include "../Blackboard.h"

#include<iostream>

Nodo_Decision_Vida_Actual_Prcnt::Nodo_Decision_Vida_Actual_Prcnt(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

Nodo_Decision_Vida_Actual_Prcnt::~Nodo_Decision_Vida_Actual_Prcnt() {

}

enum Enum_Acciones Nodo_Decision_Vida_Actual_Prcnt::toma_decision(Blackboard* _blackboard){
	float _vida = _blackboard->get_porcentaje_vida();
	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_vida >= _valor) {
		return _nodo_der->toma_decision(_blackboard);
	}
	return _nodo_izq->toma_decision(_blackboard);
}
