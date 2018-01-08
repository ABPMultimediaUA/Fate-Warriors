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
#include "../Interfaz/Motor.h"
#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    :Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad),
    _danyo_ataque_normal(_i_danyo_ataque_normal), _danyo_ataque_fuerte(_i_danyo_ataque_fuerte),_tiene_arma_corta(false),
    _tiene_arma_larga(false) {

    _inventario = new Inventario();
    _tiempo = Time::Instance();
    _accion = Nada;
    _tipo_ataque = Ataque_Ninguno;
}

Character::~Character() {
    delete _inventario;
}

int16_t Character::get_vida(){
	return _vida;
}

void Character::modificar_vida_en(short _i_vida){

	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida < 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
}

void Character::danyar(short _danyo){
    _vida = _vida - _danyo;

    if(_accion == Accion_pre_atacar){
        set_accion(Recibir_danyo);
        std::cout << "Ataque cortado" << std::endl;
    }

    if(_vida < 0){
        morir();
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
    if(_tiene_arma_corta==true){
        _rango_arma_corta=_inventario->get_objeto_cerca()->get_rango();
        return &_rango_arma_corta;
    }
		
}
uint8_t* Character::get_ref_rango_arma_larga(){
	if(_tiene_arma_larga==true){
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

void Character::gestion_acciones(){
    gestion_ataque();
    gestion_dash();
}

void Character::gestion_dash(){
    if(get_accion() == Accion_Dash){
        std::cout << "ESQUIVANDO" << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

void Character::gestion_ataque(){

    if(this->get_accion() == Accion_pre_atacar){
        std::cout << "PRE-ATACANDO" << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            
        }
    }
    else if(this->get_accion() == Atacar){

        NPC_Manager * _npc_manager = Game::game_instancia()->game_get_datos()->get_npc_manager();
        NPC ** _npcs = _npc_manager->get_npcs();
        uint16_t _cont, _n_npcs;
        _n_npcs = _npc_manager->get_n_enemigos();

        for(_cont = 0; _cont < _n_npcs; _cont++) {
            if( //_npcs[_cont]->get_blackboard()->get_tipo_enemigo() != Aliado && 
                comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _npcs[_cont]->get_vector(), 3) == true)
            {
                if(this->get_tipo_ataque() == Ataque_Normal){
                _npcs[_cont]->modificar_vida_en(-this->_danyo_ataque_normal);
                }
                else if(this->get_tipo_ataque()  == Ataque_Fuerte){
                    _npcs[_cont]->modificar_vida_en(-this->_danyo_ataque_fuerte);
                }  
                std::cout << "----- " << _npcs[_cont]->get_vida() << "------" << std::endl;
            }
        }
        std::cout << "ATACANDO" << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Accion_post_atacar);
        }
    }
    else if(this->get_accion() == Accion_post_atacar){
        std::cout << "POST-ATACANDO" << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

void Character::atacar(Enum_Tipo_Ataque _i_tipo_ataque){
    // Ataque de player y aliados, sobrescrbir en Enemigo
    // Se ataca a enemigos
    if(this->get_tipo_ataque() == Ataque_Ninguno && esta_bloqueado() == false){
        this->set_accion(Accion_pre_atacar);
        this->set_tipo_ataque(_i_tipo_ataque);
    }
    else if(this->get_accion() == Accion_post_atacar){
        std::cout << "ENLAZA ATAQUE" << std::endl;
        this->set_accion(Accion_pre_atacar);
        this->set_tipo_ataque(_i_tipo_ataque);
    }
    
}

void Character::esquivar(uint16_t _direccion){
    // Ataque de player y aliados, sobrescrbir en Enemigo
    // Se ataca a enemigos
    if(esta_bloqueado() == false){
        set_accion(Accion_Dash);
        _motor->Dash(_direccion,_id_motor);
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
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _llaves[_cont]->get_vector(), 3) == true)
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
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _puertas[_cont]->get_vector(), 3) == true)
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

void Character::bloquear_input(double _i_duracion_bloqueo_actual){
    _tiempo_inicio_bloqueado = _tiempo->get_current();
    _duracion_bloqueo_actual = _i_duracion_bloqueo_actual;
    //_bloqueado = true;
}

void Character::desbloquear_input(){
    _duracion_bloqueo_actual = 0;
}

void Character::morir(){
    std::cout << "He muerto :("<< std::endl;
}

Enum_Acciones Character::get_accion(){
    return _accion;
}

static int getTiempoAccion(Enum_Acciones _accion){
    switch(_accion)
    {
        case Accion_pre_atacar:
            return 500;
        case Atacar:
            return 1;
        case Accion_post_atacar:
            return 500;
        case Accion_Dash:
            return 500;
        default:
            return 500;
    }
}

void Character::set_accion(Enum_Acciones _i_accion){
    _accion = _i_accion;
    if(_i_accion != Nada){ // Si es Nada no se bloquean inputs
        bloquear_input(getTiempoAccion(_i_accion)); // hacer parametro dinamico
    }

    if(_i_accion != Accion_pre_atacar && _i_accion != Accion_post_atacar && _i_accion != Atacar){
        set_tipo_ataque(Ataque_Ninguno);
    }
}

Enum_Tipo_Ataque Character::get_tipo_ataque(){
    return _tipo_ataque;
}

void Character::set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque){
    _tipo_ataque = _i_tipo_ataque;
}

bool Character::esta_bloqueado(){
    if(_tiempo->get_current() - _tiempo_inicio_bloqueado < _duracion_bloqueo_actual){
        return true;
    }
    else{
        return false;
    }
}
