#include "ND_2.h" 
 
#include "../Blackboard.h" 
#include "../../Personajes/NPC.h" 

#include<iostream> 
 
ND_2::ND_2(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) { 
  _valor = _i_valor; 
} 
 
ND_2::~ND_2() { 
 
} 
 
enum Enum_Acciones ND_2::toma_decision(Blackboard* _blackboard){ 
 
    //std::cout <<"Entra ND_2\n"; 
  if(_blackboard->_estoy_en_mi_zona == true) { // TRUE, es 1 
        //std::cout <<"_enemigo_mas_cerca_esta_muy_cerca\n"; 
    return _nodo_der->toma_decision(_blackboard); 
  } 

  //std::cout << "llega NODO 2 HIJO IZQ\n";
    //std::cout <<"_enemigo_mas_cerca_ NO esta_muy_cerca\n"; 
  return _nodo_izq->toma_decision(_blackboard); 
} 