#include "Nodo_Decision_Final.h"

Nodo_Decision_Final::Nodo_Decision_Final(enum Enum_Acciones _i_accion) {
	_accion = _i_accion;
}

Nodo_Decision_Final::~Nodo_Decision_Final() {

}

enum Enum_Acciones Nodo_Decision_Final::nodo_decision_toma_decision(Blackboard* _blackboard){
	return _accion;
}
