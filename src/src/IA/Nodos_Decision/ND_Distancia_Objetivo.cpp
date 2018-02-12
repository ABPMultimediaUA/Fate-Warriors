#include "ND_Distancia_Objetivo.h"

#include "../Blackboard.h"

#include<iostream>

ND_Distancia_Objetivo::ND_Distancia_Objetivo(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Distancia_Objetivo::~ND_Distancia_Objetivo() {

}

enum Enum_Acciones ND_Distancia_Objetivo::toma_decision(Blackboard* _blackboard){
	float _distancia = _blackboard->get_distancia_objetivo();
	//std::cout << "distancia= " << _distancia << " y el valor es " << _valor << "\n";
	if(_distancia >= _valor) {
		return _nodo_der->toma_decision(_blackboard);
	}
	return _nodo_izq->toma_decision(_blackboard);
}
