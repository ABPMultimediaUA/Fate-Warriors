#include "Nodo_Decision_Final.h"

Nodo_Decision_Final::Nodo_Decision_Final(enum Enum_Acciones _i_accion, Interfaz_Toma_Decision& _i_interfaz, Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der) : Nodo_Decision(_i_interfaz, _i_nodo_izq, _i_nodo_der) {
	_accion = _i_accion;
}

Nodo_Decision_Final::~Nodo_Decision_Final() {

}

enum Enum_Acciones Nodo_Decision_Final::nodo_decision_toma_decision(unsigned short _i_n_enemigo){
	return _accion;
}
