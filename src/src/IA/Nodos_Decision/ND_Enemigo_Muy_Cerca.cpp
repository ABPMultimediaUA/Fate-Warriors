#include "ND_Enemigo_Muy_Cerca.h"

#include "../Blackboard.h"
#include "../../Personajes/Character.h"

#include<iostream>

ND_Enemigo_Muy_Cerca::ND_Enemigo_Muy_Cerca(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Enemigo_Muy_Cerca::~ND_Enemigo_Muy_Cerca() {

}

enum Enum_Acciones ND_Enemigo_Muy_Cerca::toma_decision(Blackboard* _blackboard){
	Character * enemy = _blackboard->_enemigo_mas_cerca;
	_blackboard->objetivo_x = enemy->getX();
	_blackboard->objetivo_y = enemy->getZ();

	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_blackboard->_enemigo_mas_cerca_menos_de_6_metros == true) { // TRUE, es 1
		return _nodo_der->toma_decision(_blackboard);
        // Atacar
	}
    //Andar (perseguir al enemigo)
	return _nodo_izq->toma_decision(_blackboard);
}
