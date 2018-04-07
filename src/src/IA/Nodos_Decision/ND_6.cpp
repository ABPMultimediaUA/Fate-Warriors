#include "ND_6.h"

#include "../Blackboard.h"
#include "../../Personajes/Character.h"

//#include<iostream>

ND_6::ND_6(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_6::~ND_6() {

}

enum Enum_Acciones ND_6::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_6\n";
	if( _blackboard->_puedo_esquivar == true) { // TRUE, es 1
        // Esquivar
        //std::cout <<"_tengo_arma_corta_distancia\n";
		return _nodo_der->toma_decision(_blackboard);
	}
	// Atacar
    //std::cout <<"NO _tengo_arma_corta_distancia\n";
	return _nodo_izq->toma_decision(_blackboard);
}
