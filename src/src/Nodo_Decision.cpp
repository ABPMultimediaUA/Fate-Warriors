#include "Nodo_Decision.h"

Nodo_Decision::Nodo_Decision(Interfaz_Toma_Decision& _i_interfaz, Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der){
	_interfaz = &_i_interfaz;
	_nodo_izq = &_i_nodo_izq;
	_nodo_der = &_i_nodo_der;
}

Nodo_Decision::~Nodo_Decision() {

}

