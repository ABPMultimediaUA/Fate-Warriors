#include "Action_Manager.h"

#include "IA/Blackboard.h"
#include "IA/Enum_Acciones.h"
#include "IA/Interfaz_Datos.h"
#include "IA/Path_Manager.h"

#include "Personajes/NPC.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Game.h"
#include "Datos_Partida.h"
#include "Interactuable_Manager.h"
#include "Llave.h"
#include "Puerta.h"
#include "Inventario.h"

#include<iostream>
#include<vector>

Action_Manager::Action_Manager() {
	_interfaz_decision = new Interfaz_Datos();

	_path_manager = new Path_Manager(*_interfaz_decision);
}

Action_Manager::~Action_Manager() {
	delete _path_manager;

	delete _interfaz_decision;
}

void Action_Manager::realiza_accion(NPC* _i_npc){
	
	Blackboard* _blackboard = _i_npc->get_blackboard();

	enum Enum_Acciones _accion = _blackboard->get_accion();
	unsigned short _n_enemigo = _blackboard->get_n_enemigo();


	switch(_accion) {
		case Andar:
			unsigned short _direccion;

			_direccion = _path_manager->get_direccion_movimiento(_n_enemigo);

			_i_npc->move(_direccion);

			break;

		case Atacar:
		//	std::cout << "El enemigo " << _n_enemigo << " ataca" << std::endl;
			//ATACAR
			break;

		case Decidir:
		//	std::cout << "El enemigo " << _n_enemigo << " decide" << std::endl;
			break;
		case Nada:
		//	std::cout << "El enemigo " << _n_enemigo << " hace nada" << std::endl;
			break;
	}
}


void Action_Manager::mover(Character* _i_personaje, unsigned short _i_direccion) {
	//Comprobar que se puede mover
	//_i_personaje->move(_direccion);
}

void Action_Manager::comprobar_objetos_interactuables_cercanos(Character* _i_personaje) {
	//Busca el objeto interactuable mas cercano e interactua con el (recogerlo, abrirlo, etc.)

    Interactuable_Manager * _int_man  = Game::game_instancia()->game_get_datos()->get_interactuable_manager();
    
    Llave** _llaves = _int_man->get_llaves();
    Puerta** _puertas = _int_man->get_puertas();
    
    unsigned short _cont;
    bool objeto_encontrado = false;

    // Busca llave y la coge

    for(_cont = 0; _cont < _int_man->get_n_llaves() && objeto_encontrado == false; _cont++) {
		if( _llaves[_cont]->get_visible() == true && 
            comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 20.0, _llaves[_cont]->get_vector(), 20.0) == true)
        {
            // Recoge llave y la anyade al inventario
            
            _i_personaje->get_inventario()->anadir_llave(_llaves[_cont]);
            _llaves[_cont]->set_visible(false);

            objeto_encontrado = true;
            std::cout << "Llave recogida"<< std::endl;
            std::cout << "Llaves: "<< _i_personaje->get_inventario()->get_llaves().size() << std::endl;
        }
	}
	
    // Busca puerta y la abre

	for(_cont = 0; _cont < _int_man->get_n_puertas() && objeto_encontrado == false; _cont++) {
		if( _puertas[_cont]->get_visible() == true && 
            _puertas[_cont]->get_abierta() == false && 
            comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 20.0, _puertas[_cont]->get_vector(), 20.0) == true)
        {
            std::vector<Llave*> _llaves_character = _i_personaje->get_inventario()->get_llaves();
            
            for (short i = 0; i < _llaves_character.size(); ++i) {
                if(_llaves_character[i]->get_id_puerta() == _puertas[_cont]->get_id()){
                    // Abre puerta y elimina la llave del inventario

                    _puertas[_cont]->set_abierta(true);
                    _i_personaje->get_inventario()->eliminar_llave(_llaves_character[i]);
                    objeto_encontrado = true;

                    std::cout << "Puerta abierta"<< std::endl;
                    std::cout << "Llaves: "<< _i_personaje->get_inventario()->get_llaves().size() << std::endl;
                }
            }
        }
	}
}

static void atacar_normal(Character* _i_atacante, Character* _i_atacado){
    _i_atacado->modificar_vida_en(-(_i_atacante->get_danyo_ataque_normal()));
    std::cout << _i_atacado->get_vida() << std::endl;
    std::cout << "-----------------------------"<< std::endl;
}
    
void Action_Manager::atacar(Character* _i_personaje, Enum_Tipo_Ataque _i_tipo_ataque) {

    bool es_enemigo = false, es_aliado = false, es_player = false;

    if (NPC * npc = dynamic_cast<NPC *>(_i_personaje))
    {
        if(npc->get_blackboard()->get_tipo_enemigo() == Aliado){
            es_aliado = true;
        }
        else{
            es_enemigo = true;
        }
    }
    else if (Player * player = dynamic_cast<Player *>(_i_personaje))
    {
       es_player = true;
    }

    if(es_player == true || es_aliado == true){
        // Se ataca a enemigos
        NPC_Manager * _npc_manager = Game::game_instancia()->game_get_datos()->get_npc_manager();
        NPC ** _npcs = _npc_manager->get_npcs();
        unsigned long _cont;
        
        for(_cont = 0; _cont < _npc_manager->get_n_enemigos(); _cont++) {
            if( _npcs[_cont]->get_blackboard()->get_tipo_enemigo() != Aliado && 
                comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 40.0, _npcs[_cont]->get_vector(), 40.0) == true)
            {
                if(_i_tipo_ataque == Ataque_Normal){
                    atacar_normal(_i_personaje, _npcs[_cont]);
                }
                else if(_i_tipo_ataque == Ataque_Fuerte){

                }  
            }
        }

    }
    else if(es_enemigo == true){
        // Se ataca a player y aliados

        // Ataque a aliados
        NPC_Manager * _npc_manager = Game::game_instancia()->game_get_datos()->get_npc_manager();
        NPC ** _npcs = _npc_manager->get_npcs();
        unsigned long _cont;
        
        for(_cont = 0; _cont < _npc_manager->get_n_enemigos(); _cont++) {
            if( _npcs[_cont]->get_blackboard()->get_tipo_enemigo() == Aliado && 
                comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 40.0, _npcs[_cont]->get_vector(), 40.0) == true)
            {
                if(_i_tipo_ataque == Ataque_Normal){
                    atacar_normal(_i_personaje, _npcs[_cont]);
                }
                else if(_i_tipo_ataque == Ataque_Fuerte){
                    
                }
            }
        }

        // Ataque a player
        Player * _player = Game::game_instancia()->game_get_datos()->get_player();
        if(comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 40.0, _player->get_vector(), 40.0) == true)
        {
            if(_i_tipo_ataque == Ataque_Normal){
                atacar_normal(_i_personaje, _player);
            }
            else if(_i_tipo_ataque == Ataque_Fuerte){
                
            }
        }

    }


}


Interfaz_Datos* Action_Manager::get_interfaz() {
	return _interfaz_decision;
}
