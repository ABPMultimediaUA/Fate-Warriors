#include "Nodo_Decision_Tipo.h"

Nodo_Decision_Tipo::Nodo_Decision_Tipo(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {

}

Nodo_Decision_Tipo::~Nodo_Decision_Tipo() {

}

enum Enum_Acciones Nodo_Decision_Tipo::nodo_decision_toma_decision(Blackboard* _blackboard){
	return _nodo_der->nodo_decision_toma_decision(_blackboard);
}

