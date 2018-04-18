#include "Nodo_Decision_LOD.h"

#include "../Blackboard.h"

//#include<iostream>

Nodo_Decision_LOD::Nodo_Decision_LOD(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, unsigned short _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

Nodo_Decision_LOD::~Nodo_Decision_LOD() {

}

enum Enum_Acciones Nodo_Decision_LOD::toma_decision(Blackboard* _blackboard){
	int8_t _lod = _blackboard->get_level_of_detail();

	if(_lod > _valor) {
		return _nodo_izq->toma_decision(_blackboard);
	}
	return _nodo_der->toma_decision(_blackboard);
}
