#include "Experto_Combate.h"

#include "Blackboard.h"
#include "Nodo_Decision.h"

#include <iostream>

Experto_Combate::Experto_Combate(Nodo_Decision *_i_arbol_decision) : Experto(_i_arbol_decision){

}

Experto_Combate::~Experto_Combate() {

}


bool Experto_Combate::leer_blackboard(Blackboard* _blackboard) {
	if(_blackboard->get_distancia_jugador() < 20) {
		return true;
	}
	return false;
}

enum Enum_Acciones Experto_Combate::toma_decision(Blackboard* _blackboard) {
	return _arbol_decision->nodo_decision_toma_decision(_blackboard);
}
