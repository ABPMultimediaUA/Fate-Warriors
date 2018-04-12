#include "ND_0.h" 
 
#include "../Blackboard.h" 
#include "../../Personajes/Character.h" 
 
#include<iostream> 
 
ND_0::ND_0(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) { 
  _valor = _i_valor; 
} 
 
ND_0::~ND_0() { 
 
} 
 
enum Enum_Acciones ND_0::toma_decision(Blackboard* _blackboard){ 
 
  //std::cout <<"Entra ND_0\n"; 
  if(_blackboard->_enemigo_mas_cerca_esta_muy_cerca == true) { // TRUE, es 1 
      //std::cout <<"_enemigo_mas_cerca_esta_muy_cerca\n"; 
      //std::cout <<"ATACAR\n"; 
    return _nodo_der->toma_decision(_blackboard); 
  } 

  // Seguir a enemigo mas cerca 
  Character * enemigo = _blackboard->_enemigo_mas_cerca; 

  if(enemigo != nullptr){
    _blackboard->objetivo_x = enemigo->getX(); 
    _blackboard->objetivo_y = enemigo->getZ(); 

    //std::cout << "seguir enemigos \n";
    //std::cout <<_blackboard->objetivo_x << _blackboard->objetivo_y <<"\n";
  }
  else{
    std::cout << "ERROR NODO 0 \n";
  }
  
  //std::cout <<"sEGUIR A ENEMIGO MAS CERCA\n"; 
  return _nodo_izq->toma_decision(_blackboard); 
} 