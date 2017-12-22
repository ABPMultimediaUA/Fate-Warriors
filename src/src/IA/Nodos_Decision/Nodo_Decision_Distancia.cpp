#include "Nodo_Decision_Distancia.h"

#include "../Blackboard.h"

#include<iostream>

Nodo_Decision_Distancia::Nodo_Decision_Distancia(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

Nodo_Decision_Distancia::~Nodo_Decision_Distancia() {

}

enum Enum_Acciones Nodo_Decision_Distancia::toma_decision(Blackboard* _blackboard){
	float _distancia = _blackboard->get_distancia_jugador();
	//std::cout << "distancia= " << _distancia << " y el valor es " << _valor << "\n";
	if(_distancia >= _valor) {
		return _nodo_der->toma_decision(_blackboard);
	}
	return _nodo_izq->toma_decision(_blackboard);
}
