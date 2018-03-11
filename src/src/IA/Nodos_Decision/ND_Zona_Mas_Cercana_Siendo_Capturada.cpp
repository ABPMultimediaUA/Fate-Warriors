#include "ND_Zona_Mas_Cercana_Siendo_Capturada.h"

#include "../Blackboard.h"
#include "../../Zona.h"
#include "../../Personajes/NPC.h"

#include<iostream>

ND_Zona_Mas_Cercana_Siendo_Capturada::ND_Zona_Mas_Cercana_Siendo_Capturada(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Zona_Mas_Cercana_Siendo_Capturada::~ND_Zona_Mas_Cercana_Siendo_Capturada() {

}

enum Enum_Acciones ND_Zona_Mas_Cercana_Siendo_Capturada::toma_decision(Blackboard* _blackboard){

    

	//std::cout << "% vida = " << _vida << " y el valor es " << _valor << "\n";
	if(_blackboard->_zona_mas_cerca->siendo_capturada() == true) { // TRUE, es 1
	std::cout <<"zona mas cerca capturando \n";
        _blackboard->objetivo_x = _blackboard->_zona_mas_cerca->getX();
        _blackboard->objetivo_y = _blackboard->_zona_mas_cerca->getZ();
		return _nodo_der->toma_decision(_blackboard);
	}
	std::cout <<"zona mas cerca NO capturando \n";
    _blackboard->objetivo_x = _blackboard->_zona_enemiga_mas_cerca->getX();
    _blackboard->objetivo_y = _blackboard->_zona_enemiga_mas_cerca->getZ();
	return _nodo_izq->toma_decision(_blackboard);
}
