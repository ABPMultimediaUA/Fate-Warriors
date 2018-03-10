#include "ND_3.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"
#include "../../Interruptor.h"
#include "../../Puerta_Pincho.h"
#include "../../Interfaz_Libs/Lib_Math.h"

#include<iostream>

ND_3::ND_3(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_3::~ND_3() {

}

enum Enum_Acciones ND_3::toma_decision(Blackboard* _blackboard){

    Interruptor * interruptor_util = nullptr;

    float distancia_a_interruptor_mas_cerca = 1000000000;

    Zona* zona_actual = _blackboard->_zona_actual;
    std::vector<Interruptor*> interruptores = zona_actual->get_interruptores_asociados();

    short tamanio = interruptores.size();

    for(short i = 0; i < tamanio; i++){
        Zona* zona1 = interruptores[i]->get_puerta()->get_zona_1();
        Zona* zona2 = interruptores[i]->get_puerta()->get_zona_2();

        float distancia_a_interruptor = lib_math_distancia_2_puntos(interruptores[i]->getX(), interruptores[i]->getZ(), _blackboard->_npc_padre->getX(), _blackboard->_npc_padre->getZ());

        if(zona1 != zona_actual && zona1->get_equipo() != _blackboard->_npc_padre->get_equipo() 
            && distancia_a_interruptor < distancia_a_interruptor_mas_cerca && interruptores[i]->get_puerta()->ha_pasado_tiempo_suficiente()){
            interruptor_util = interruptores[i];
            distancia_a_interruptor_mas_cerca = distancia_a_interruptor;
        }
        else if(zona2 != zona_actual && zona2->get_equipo() != _blackboard->_npc_padre->get_equipo() 
            && distancia_a_interruptor < distancia_a_interruptor_mas_cerca && interruptores[i]->get_puerta()->ha_pasado_tiempo_suficiente()){
            interruptor_util = interruptores[i];
            distancia_a_interruptor_mas_cerca = distancia_a_interruptor;
        }
    }

    _blackboard->_interruptor_cerca_util = interruptor_util;

    //std::cout <<"Entra ND_3\n";
	if(interruptor_util != nullptr && _blackboard->_habilidad_activar_interruptor == true) { // TRUE, es 1
        //std::cout <<"SI hay interruptor usable y util\n";
		return _nodo_der->toma_decision(_blackboard);
	}
    // Nada
    //_blackboard->objetivo_x = _blackboard->_zona_actual->getX();
    //_blackboard->objetivo_y = _blackboard->_zona_actual->getZ();
    //std::cout <<"NO hay interruptor usable y util\n";
	return _nodo_izq->toma_decision(_blackboard);
}