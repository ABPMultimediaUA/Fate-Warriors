#include "Action_Manager.h"

#include "IA/Blackboard.h"
#include "IA/Enum_Acciones.h"
#include "IA/Path_Manager.h"

#include "Personajes/NPC.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Game.h"

#include<iostream>
#include<vector>

Action_Manager::Action_Manager() {
	_path_manager = new Path_Manager();
}

Action_Manager::~Action_Manager() {
	delete _path_manager;
}

void Action_Manager::realiza_accion(NPC* _i_npc){
	
	Blackboard* _blackboard = _i_npc->get_blackboard();
	float x,z;
	enum Enum_Acciones _accion = _i_npc->get_accion();

	switch(_accion) {
		case Andar:
			if(!_i_npc->esta_bloqueado()) {
				unsigned short _direccion;
				x=_i_npc->getX();
				z=_i_npc->getZ();
				_direccion = _path_manager->get_direccion_movimiento(x,z);
				if(_direccion!=362){
					// Componenetes de la direccion mala
					float _cos, _sen;
					_cos = sin(_direccion*std::acos(-1)/180);
					_sen = cos(_direccion*std::acos(-1)/180);

					// Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
					uint16_t _nueva_direccion = atan2(_sen, _cos) * 180 / std::acos(-1);
        			while(_nueva_direccion >= 360) _nueva_direccion -= 360;

					_i_npc->mover(_nueva_direccion);
				}else{
					_i_npc->setPositionXZ(x,z);
				}
			}

			break;

		case Atacar:
			//if(dynamic_cast<Ally*>(_i_npc) == NULL) {
				//std::cout << "No es un Aliado\n";
				// Atacar al jugador/enemigo
				//_i_npc->atacar(Ataque_Normal);
			//}	
			//else {
				//std::cout << "Es un Aliado\n";
				// Atacar al enemigo
			//}
			//_i_npc->stop();
		//	std::cout << "El enemigo " << _n_enemigo << " ataca" << std::endl;
			//ATACAR
			break;

		case Decidir:
			//_i_npc->stop();
		//	std::cout << "El enemigo " << _n_enemigo << " decide" << std::endl;
			break;
		case Nada:
			//_i_npc->stop();
		//	std::cout << "El enemigo " << _n_enemigo << " hace nada" << std::endl;
			break;
		case Huir:
			//std::cout << "HUYO\n";
			break;
		default:
			//_i_npc->stop();
			break;
	}
}


void Action_Manager::mover(Character* _i_personaje, unsigned short _i_direccion) {
	//Comprobar que se puede mover
	//_i_personaje->move(_direccion);
}