#include "Action_Manager.h"

#include "IA/Blackboard.h"
#include "IA/Enum_Acciones.h"
#include "IA/Interfaz_Datos.h"
#include "IA/Path_Manager.h"

#include "Personajes/NPC.h"
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
    
    for(_cont = 0; _cont < _int_man->get_n_llaves(); _cont++) {
		if( _llaves[_cont]->get_visible() == true && 
            comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 20.0, _llaves[_cont]->get_vector(), 20.0) == true)
        {
            std::cout << "Llave recogida"<< std::endl;
            _i_personaje->get_inventario()->anadir_llave(_llaves[_cont]);
            _llaves[_cont]->set_visible(false);
        }
        //else{
          //  std::cout << "NO Puede coger llave"<< std::endl;
       // }
	}
	
	for(_cont = 0; _cont < _int_man->get_n_puertas(); _cont++) {
		if( _puertas[_cont]->get_visible() == true && 
            comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 20.0, _puertas[_cont]->get_vector(), 20.0) == true)
        {
            std::vector<Llave*> _llaves_character = _i_personaje->get_inventario()->get_llaves();
            
            for (short i = 0; i < _llaves_character.size(); ++i) {
                if(_llaves_character[i]->get_id_puerta() == _puertas[_cont]->get_id()){
                    std::cout << "Puede abrirla"<< std::endl;
                }
            }
            
            //std::cout << "Puede intentar abrir puerta"<< std::endl;
        }
	}
    
    /*
    std::cout<<_llave->getX() <<std::endl;
    //std::cout<< &_llave <<std::endl;
    std::cout<<_i_personaje->getX() <<std::endl;
    //std::cout<< &_i_personaje <<std::endl;
    
    std::cout<<_llave->getZ() <<std::endl;
     std::cout<<_i_personaje->getZ() <<std::endl;
     
    if(comprobar_colision_teniendo_tambien_radio(_i_personaje->get_vector(), 50.0, _llave->get_vector(), 50.0) == true){
        std::cout << "Puede coger"<< std::endl;
    }
    else{
        std::cout << "NO Puede coger"<< std::endl;
    }
    */
}



Interfaz_Datos* Action_Manager::get_interfaz() {
	return _interfaz_decision;
}
