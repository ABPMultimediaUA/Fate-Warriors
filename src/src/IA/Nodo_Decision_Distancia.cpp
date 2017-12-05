#include "Nodo_Decision_Distancia.h"

#include "Blackboard.h"

#include<iostream>

Nodo_Decision_Distancia::Nodo_Decision_Distancia(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {

}

Nodo_Decision_Distancia::~Nodo_Decision_Distancia() {

}

enum Enum_Acciones Nodo_Decision_Distancia::nodo_decision_toma_decision(Blackboard* _blackboard){
	float distancia = _blackboard->get_distancia_jugador();

	if(distancia > 2) {
		return _nodo_izq->nodo_decision_toma_decision(_blackboard);
	}
	return _nodo_der->nodo_decision_toma_decision(_blackboard);
}
