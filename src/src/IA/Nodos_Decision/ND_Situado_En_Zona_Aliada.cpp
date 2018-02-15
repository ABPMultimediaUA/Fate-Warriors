#include "ND_Situado_En_Zona_Aliada.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_Situado_En_Zona_Aliada::ND_Situado_En_Zona_Aliada(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Situado_En_Zona_Aliada::~ND_Situado_En_Zona_Aliada() {

}

enum Enum_Acciones ND_Situado_En_Zona_Aliada::toma_decision(Blackboard* _blackboard){

	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_blackboard->_zona_actual->get_equipo() == _blackboard->_npc_padre->get_equipo()) { // TRUE, es 1
		return _nodo_der->toma_decision(_blackboard);
	}
	return _nodo_izq->toma_decision(_blackboard);
}
