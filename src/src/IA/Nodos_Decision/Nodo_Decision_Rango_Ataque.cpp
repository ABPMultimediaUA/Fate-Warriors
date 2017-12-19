#include "Nodo_Decision_Rango_Ataque.h"

#include "../Blackboard.h"

#include<iostream>

Nodo_Decision_Rango_Ataque::Nodo_Decision_Rango_Ataque(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, unsigned short _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

Nodo_Decision_Rango_Ataque::~Nodo_Decision_Rango_Ataque() {

}

enum Enum_Acciones Nodo_Decision_Rango_Ataque::toma_decision(Blackboard* _blackboard){
	unsigned short _lod = _blackboard->get_rango_ataque();

	if(_lod > _valor) {
		return _nodo_izq->toma_decision(_blackboard);
	}
	return _nodo_der->toma_decision(_blackboard);
}
