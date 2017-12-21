#include "Character.h"
#include "../Armas/Arma_distancia.h"
#include "../Armas/Arma_cerca.h"
#include "../Inventario.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "NPC.h"
#include "NPC_Manager.h"
#include "../Llave.h"
#include "../Puerta.h"
#include "../Interactuable_Manager.h"
#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    :Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad),
    _danyo_ataque_normal(_i_danyo_ataque_normal), _danyo_ataque_fuerte(_i_danyo_ataque_fuerte) {

    _inventario = new Inventario();
}

Character::~Character() {
    delete _inventario;
}

short Character::get_vida(){
	return _vida;
}

void Character::modificar_vida_en(short _i_vida){

	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida < 0){
        this->morir();
    }
    else{
        _vida+=_i_vida;
    }
}

void Character::set_vida(short _i_vida){
	_vida=_i_vida;
}

Inventario* Character::get_inventario(){
    return _inventario;
}

bool Character::isDead(){
    if(_vida>0){
        return false;
    }
    return true;
}

bool Character::puede_subir_vida_(short _i_vida){
    if(_vida==_vida_maxima){
        return false;
    }
    return true;
}

uint8_t* Character::get_ref_rango_arma_corta(){
    if(_tiene_arma_corta){
        _rango_arma_corta=_inventario->get_objeto_cerca()->get_rango();
        return &_rango_arma_corta;
    }
		
}
uint8_t* Character::get_ref_rango_arma_larga(){
	if(_tiene_arma_larga){
        _rango_arma_larga=_inventario->get_objeto_distancia()->get_rango();
        return &_rango_arma_larga;
    }
}

short Character::get_danyo_ataque_normal(){
	return _danyo_ataque_normal;
}

short Character::get_danyo_ataque_fuerte(){
	return _danyo_ataque_fuerte;
}

void Character::atacar(Enum_Tipo_Ataque _i_tipo_ataque){
    // Ataque de player y aliados
    // Se ataca a enemigos

    NPC_Manager * _npc_manager = Game::game_instancia()->game_get_datos()->get_npc_manager();
    NPC ** _npcs = _npc_manager->get_npcs();
    unsigned long _cont;

    for(_cont = 0; _cont < _npc_manager->get_n_enemigos(); _cont++) {
        if( //_npcs[_cont]->get_blackboard()->get_tipo_enemigo() != Aliado && 
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 40.0, _npcs[_cont]->get_vector(), 40.0) == true)
        {
            if(_i_tipo_ataque == Ataque_Normal){
               _npcs[_cont]->modificar_vida_en(-this->_danyo_ataque_normal);
            }
            else if(_i_tipo_ataque == Ataque_Fuerte){
                _npcs[_cont]->modificar_vida_en(-this->_danyo_ataque_fuerte);
            }  
            std::cout << "----- " << _npcs[_cont]->get_vida() << "------" << std::endl;
        }
    }
}

void Character::interactuar_con_objeto(){
    //Busca el objeto interactuable mas cercano e interactua con el (recogerlo, abrirlo, etc.)

    Interactuable_Manager * _int_man  = Game::game_instancia()->game_get_datos()->get_interactuable_manager();
    
    Llave** _llaves = _int_man->get_llaves();
    Puerta** _puertas = _int_man->get_puertas();
    
    unsigned short _cont;
    bool objeto_encontrado = false;

    // Busca llave y la coge

    for(_cont = 0; _cont < _int_man->get_n_llaves() && objeto_encontrado == false; _cont++) {
		if( _llaves[_cont]->get_visible() == true && 
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 20.0, _llaves[_cont]->get_vector(), 20.0) == true)
        {
            // Recoge llave y la anyade al inventario
            
            this->get_inventario()->anadir_llave(_llaves[_cont]);
            _llaves[_cont]->set_visible(false);

            objeto_encontrado = true;
            std::cout << "Llave recogida"<< std::endl;
            std::cout << "Llaves: "<< this->get_inventario()->get_llaves().size() << std::endl;
        }
	}
	
    // Busca puerta y la abre

	for(_cont = 0; _cont < _int_man->get_n_puertas() && objeto_encontrado == false; _cont++) {
		if( _puertas[_cont]->get_visible() == true && 
            _puertas[_cont]->get_abierta() == false && 
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 20.0, _puertas[_cont]->get_vector(), 20.0) == true)
        {
            std::vector<Llave*> _llaves_character = this->get_inventario()->get_llaves();
            
            for (short i = 0; i < _llaves_character.size(); ++i) {
                if(_llaves_character[i]->get_id_puerta() == _puertas[_cont]->get_id()){
                    // Abre puerta y elimina la llave del inventario

                    _puertas[_cont]->set_abierta(true);
                    this->get_inventario()->eliminar_llave(_llaves_character[i]);
                    objeto_encontrado = true;

                    std::cout << "Puerta abierta"<< std::endl;
                    std::cout << "Llaves: "<< this->get_inventario()->get_llaves().size() << std::endl;
                }
            }
        }
	}
}

void Character::bloquear_movimiento(double i_tiempo_inicio_bloqueado){
    _tiempo_inicio_bloqueado = i_tiempo_inicio_bloqueado;
    _bloqueado = true;
}

double Character::get_tiempo_inicio_bloqueado(){
    return _tiempo_inicio_bloqueado;
}

void Character::set_bloqueado(bool _i_bloqueado){
    _bloqueado = _i_bloqueado;
}

bool Character::get_bloqueado(){
    return _bloqueado;
}

void Character::morir(){
    std::cout << "He muerto :("<< std::endl;
}