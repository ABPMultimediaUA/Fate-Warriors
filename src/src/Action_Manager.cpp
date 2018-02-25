#include "Action_Manager.h"

#include "IA/Blackboard.h"
#include "IA/Enum_Acciones.h"
#include "IA/Path_Manager.h"

#include "Personajes/NPC.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Interfaz_Libs/Lib_Math.h"
#include "Interfaz/Motor.h"
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
	enum Enum_Acciones _accion = _blackboard->get_accion();

	switch(_accion) {
		case Andar:
			if(!_i_npc->esta_bloqueado()) {
				unsigned short _direccion;
				x=_i_npc->getX();
				z=_i_npc->getZ();
				_direccion = _path_manager->get_direccion_movimiento(x,z, _i_npc->get_blackboard()->objetivo_x, _i_npc->get_blackboard()->objetivo_y);
				//std::cout << _direccion<<" \n ";
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
				//	std::cout << " ERRRRRORRRRRRRRRRRRR -----------------\n ";
					_i_npc->setPositionXZ(x,z);
				}
			}

			break;

		case Atacar:
				{
								
				x=_i_npc->getX();
				z=_i_npc->getZ();
				Character* enemigo = _blackboard->_enemigo_mas_cerca;
				uint16_t angulo_giro = lib_math_angulo_2_puntos(x, z, enemigo->getX(), enemigo->getZ());
				
				float _cos, _sen;
				_cos = sin(angulo_giro*std::acos(-1)/180);
				_sen = cos(angulo_giro*std::acos(-1)/180);

				// Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
				uint16_t _nueva_direccion = atan2(_sen, _cos) * 180 / std::acos(-1);
				while(_nueva_direccion >= 360) _nueva_direccion -= 360;


			//	std::cout << (int)_nueva_direccion << std::endl;
			//	Motor::Motor_GetInstance()->rotar_rb(_i_npc->get_objeto_motor()->getRigidBody(), angulo_giro);
				_i_npc->rotar_cuerpo(_nueva_direccion);
				_i_npc->set_direccion_actual(_nueva_direccion);

				_i_npc->atacar(_i_npc->get_blackboard()->_ataque_a_realizar);
				}

			break;
		
		case Accion_Dash:
				{
								
				x=_i_npc->getX();
				z=_i_npc->getZ();
				Character* enemigo = _blackboard->_enemigo_mas_cerca;
				uint16_t angulo_giro = lib_math_angulo_2_puntos(x, z, enemigo->getX(), enemigo->getZ());
				
				if(uint16_t(x+z)%2==0){
									angulo_giro+=90;

				}
				else{
					angulo_giro-=90;
				}

				float _cos, _sen;
				_cos = sin(angulo_giro*std::acos(-1)/180);
				_sen = cos(angulo_giro*std::acos(-1)/180);

				// Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
				uint16_t _nueva_direccion = atan2(_sen, _cos) * 180 / std::acos(-1);
				while(_nueva_direccion >= 360) _nueva_direccion -= 360;


			//	std::cout << (int)_nueva_direccion << std::endl;
			//	Motor::Motor_GetInstance()->rotar_rb(_i_npc->get_objeto_motor()->getRigidBody(), angulo_giro);
				_i_npc->rotar_cuerpo(_nueva_direccion);
				_i_npc->set_direccion_actual(_nueva_direccion);
				_i_npc->esquivar(_nueva_direccion);
				//_i_npc->atacar(Ataque_Normal);
				}

		break;


		case Accion_Interactuar:
				_i_npc->intentar_recoger_arma();
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