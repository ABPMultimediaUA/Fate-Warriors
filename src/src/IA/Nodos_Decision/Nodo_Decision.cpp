#include "Nodo_Decision.h"

Nodo_Decision::Nodo_Decision() {
	_nodo_izq = nullptr;
	_nodo_der = nullptr;
}

Nodo_Decision::Nodo_Decision(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der){
	_nodo_izq = &_i_nodo_izq;
	_nodo_der = &_i_nodo_der;
}

Nodo_Decision::~Nodo_Decision() {
	_nodo_izq = nullptr;
	_nodo_der = nullptr;
}

