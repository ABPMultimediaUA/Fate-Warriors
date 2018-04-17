#include "ND_1.h" 
 
#include "../Blackboard.h" 
#include "../../Personajes/NPC.h" 
 
#include<iostream> 
 
ND_1::ND_1(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) { 
  _valor = _i_valor; 
} 
 
ND_1::~ND_1() { 
 
} 
 
enum Enum_Acciones ND_1::toma_decision(Blackboard* _blackboard){ 
 
    //std::cout <<"Entra ND_1\n"; 
  if(_blackboard->_npc_padre->get_zona()->esta_jugador_en_zona() == true && _blackboard->_enemigo_mas_cerca_esta_cerca == true) { // TRUE, es 1 
        //std::cout <<"hay enemigo cerca\n"; 
    return _nodo_der->toma_decision(_blackboard); 
  }  

  if(_blackboard->_npc_padre->get_zona() != nullptr){
    _blackboard->objetivo_x = _blackboard->_npc_padre->get_zona()->getX(); 
    _blackboard->objetivo_y = _blackboard->_npc_padre->get_zona()->getZ(); 

    //std::cout << _blackboard->_npc_padre->get_zona() <<"\n";

    //std::cout << "NPC: "<< _blackboard->_npc_padre<<"\n";
    //std::cout << "objetivo: "<<_blackboard->objetivo_x << "  "<<_blackboard->objetivo_y <<"\n";
  }
  else{
    std::cout << "ERROR NODO 1 \n";
  }
  if(_blackboard->_enemigo_mas_cerca != nullptr){ 
      _blackboard->_enemigo_mas_cerca->decrementar_npcs_persiguiendome(); 
      _blackboard->_enemigo_mas_cerca = nullptr; 
      _blackboard->_enemigo_mas_cerca_esta_cerca = false; 
      _blackboard->_enemigo_mas_cerca_esta_muy_cerca = false; 
      _blackboard->_distancia_enemigo_mas_cerca =  10000000000; 
  } 
  //std::cout <<"IR A MI ZONA NODO 1\n"; 
    //std::cout <<"NO hay enemigo cerca\n"; 
  return _nodo_izq->toma_decision(_blackboard); 
} 