#include "ND_3.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"
#include "../../Interactuables/Interruptor.h"
#include "../../Interactuables/Puerta_Pincho.h"
#include "../../Interfaz_Libs/Lib_Math.h"

#include<iostream>

ND_3::ND_3(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_3::~ND_3() {

}

enum Enum_Acciones ND_3::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_3\n";
	if(_blackboard->_interruptor_cerca_util != nullptr /*&& _blackboard->_habilidad_activar_interruptor == true*/) { // TRUE, es 1
        //std::cout <<"SI hay interruptor usable y util\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    // Andar
    _blackboard->objetivo_x = _blackboard->_zona_actual->getX();
    _blackboard->objetivo_y = _blackboard->_zona_actual->getZ();
    //std::cout <<"NO hay interruptor usable y util\n";
	return _nodo_izq->toma_decision(_blackboard);
}