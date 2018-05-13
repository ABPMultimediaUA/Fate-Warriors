#include "ND_3.h" 
 
#include "../Blackboard.h"
#include "../../Personajes/NPC.h" 
 
#include<iostream> 
 
ND_3::ND_3(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) { 
  _valor = _i_valor; 
} 
 
ND_3::~ND_3() { 
 
} 
 
enum Enum_Acciones ND_3::toma_decision(Blackboard* _blackboard){ 
 
  //std::cout <<"Entra ND_3\n"; 
  if(_blackboard->_muy_cerca_de_mi_posicion_respawn == true) { // TRUE, es 1 
      //std::cout <<"NADA\n"; 
    return _nodo_der->toma_decision(_blackboard); 
  } 

    // Seguir a mi zona de respawn
    _blackboard->objetivo_x = _blackboard->_npc_padre->get_pos_x_azar_en_zona(); 
    _blackboard->objetivo_y = _blackboard->_npc_padre->get_pos_y_azar_en_zona(); 

  //std::cout <<"sEGUIR A ENEMIGO MAS CERCA\n"; 
  return _nodo_izq->toma_decision(_blackboard); 
} 