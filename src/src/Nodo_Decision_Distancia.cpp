#include "Nodo_Decision_Distancia.h"

#include<iostream>

Nodo_Decision_Distancia::Nodo_Decision_Distancia(Interfaz_Toma_Decision& _i_interfaz, Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der) : Nodo_Decision(_i_interfaz, _i_nodo_izq, _i_nodo_der) {

}

Nodo_Decision_Distancia::~Nodo_Decision_Distancia() {

}

enum Enum_Acciones Nodo_Decision_Distancia::nodo_decision_toma_decision(unsigned short _i_n_enemigo){
	float distancia = _interfaz->interfaz_decision_distancia_enemigo_personaje(_i_n_enemigo);

	//Si esta a mas de 2, se mueve
	//Si esta a menos de 2, ataca
	if(distancia > 2) {
		return _nodo_izq->nodo_decision_toma_decision(_i_n_enemigo);
	}
	return _nodo_der->nodo_decision_toma_decision(_i_n_enemigo);
}
