#include "ND_0.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Interruptor.h"
#include "../../Personajes/NPC.h"
#include "../../Interfaz_Libs/Lib_Math.h"

#include<iostream>

ND_0::ND_0(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_0::~ND_0() {

}

enum Enum_Acciones ND_0::toma_decision(Blackboard* _blackboard){

    bool interruptor_esta_cerca = false;
    float distancia_a_interruptor = lib_math_distancia_2_puntos(_blackboard->_interruptor_cerca_util->getX(), _blackboard->_interruptor_cerca_util->getZ(), _blackboard->_npc_padre->getX(), _blackboard->_npc_padre->getY());
    
    if(distancia_a_interruptor < 1){
        interruptor_esta_cerca = true;
    }

    //std::cout <<"Entra ND_0\n";
	if( interruptor_esta_cerca == true) { // TRUE, es 1
        //std::cout <<"Interruptor muy cerca\n";
        // Interactuar
		return _nodo_der->toma_decision(_blackboard);
	}
    _blackboard->objetivo_x = _blackboard->_interruptor_cerca_util->getX();
    _blackboard->objetivo_y = _blackboard->_interruptor_cerca_util->getZ();
    //std::cout <<"Interruptor NO muy cerca\n";
    // Andar
	return _nodo_izq->toma_decision(_blackboard);
}