#include "ND_5.h"

#include "../Blackboard.h"
#include "../../Personajes/Character.h"

#include<iostream>

ND_5::ND_5(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_5::~ND_5() {

}

enum Enum_Acciones ND_5::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_5\n";
	if( _blackboard->_tengo_arma_corta_distancia == true) { // TRUE, es 1
        // Equipar arma corta distancia y atacar normal
		_blackboard->equipar_arma_corta_distancia();
		_blackboard->_ataque_a_realizar = Ataque_Normal;
        std::cout <<"_tengo_arma_corta_distancia\n";
		return _nodo_der->toma_decision(_blackboard);
	}
	// Atacar
    std::cout <<"NO _tengo_arma_corta_distancia\n";
	return _nodo_izq->toma_decision(_blackboard);
}
