#include "ND_3.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"
#include "../../Interruptor.h"
#include "../../Puerta_Pincho.h"

#include<iostream>

ND_3::ND_3(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_3::~ND_3() {

}

enum Enum_Acciones ND_3::toma_decision(Blackboard* _blackboard){

    Interruptor * interruptor_util = nullptr;

    Zona* zona_actual = _blackboard->_zona_actual;
    std::vector<Interruptor*> interruptores = zona_actual->get_interruptores_asociados();

    short tamanio = interruptores.size();

    for(short i = 0; i < tamanio; i++){
        Zona* zona1 = interruptores[i]->get_puerta()->get_zona_1();
        Zona* zona2 = interruptores[i]->get_puerta()->get_zona_2();

        if(zona1 != zona_actual && zona1->get_equipo() != _blackboard->_npc_padre->get_equipo()){
            interruptor_util = interruptores[i];
        }
        else if(zona2 != zona_actual && zona2->get_equipo() != _blackboard->_npc_padre->get_equipo()){
            interruptor_util = interruptores[i];
        }
    }

    _blackboard->_interruptor_cerca_util = interruptor_util;

    //std::cout <<"Entra ND_3\n";
	if(interruptor_util != nullptr) { // TRUE, es 1
        //std::cout <<"SI hay interruptor usable y util\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    // Nada
    //std::cout <<"NO hay interruptor usable y util\n";
	return _nodo_izq->toma_decision(_blackboard);
}