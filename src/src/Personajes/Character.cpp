#include "Character.h"
#include "../Armas/Arma_distancia.h"
#include "../Armas/Arma_cerca.h"
#include "../Armas/Armas_Manager.h"
#include "../Inventario.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "NPC.h"
#include "NPC_Manager.h"
#include "../Llave.h"
#include "../Puerta.h"
#include "../Interactuable_Manager.h"
#include "../Consumibles/Consumible_Action.h"
#include "../Interfaz/Motor.h"
//#include "../Interfaz/Objeto_Motor.h"
#include <iostream>
#include "Player.h"
#include "NPC/Ally.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Consumibles/Consumible_Fuerza.h"

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    :Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad),
    _danyo_ataque_normal(_i_danyo_ataque_normal), _danyo_ataque_fuerte(_i_danyo_ataque_fuerte),_tiene_arma_corta(false),
    _tiene_arma_larga(false) {

    _inventario = new Inventario();
    _tiempo = Time::Instance();
    _accion = Nada;
    _tipo_ataque = Ataque_Ninguno;
    _tiempo_inicio_accion = 0;
    _duracion_accion_actual = 0;
    _velocidadAndar = _i_velocidad;
    _velocidadCorrer = _i_velocidad * 2;
    _velocidad = 0;
}

Character::~Character() {
    delete _inventario;
    Game::game_instancia()->get_consumibles_action()->borrar_power_up(_power_up);
}

int16_t Character::get_vida(){
	return _vida;
}

void Character::anyadir_power_up(Consumible_Fuerza* _i_power_up){
    if(_power_up!=nullptr){
        _power_up = _i_power_up;
    }  
}

void Character::eliminar_power_up_puntero(){
        _power_up=nullptr;
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

void Character::danyar_comun(short _danyo){
    _vida = _vida - _danyo;

    if(_accion == Accion_pre_atacar){
        std::cout << "Ataque cortado" << std::endl;
    }

    set_accion(Recibir_danyo);

    if(_vida <= 0){
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

void Character::atacar(Enum_Tipo_Ataque _i_tipo_ataque){
    // Ataque de player y aliados, sobrescrbir en Enemigo
    // Se ataca a enemigos
    if(this->get_tipo_ataque() == Ataque_Ninguno && esta_bloqueado() == false){
        this->set_accion(Accion_pre_atacar);
        this->set_tipo_ataque(_i_tipo_ataque);
    }
    else if(this->get_accion() == Accion_post_atacar){
        Enum_Tipo_Ataque _ataque_combo;
        _ataque_combo = get_tipo_ataque_combo(_i_tipo_ataque);

        set_accion(Accion_pre_atacar);
        set_tipo_ataque(_ataque_combo);

         std::cout << "ENLAZA ATAQUE: ";

        if(_ataque_combo == Ataque_Normal_Normal)
            std::cout << "Ataque NORMAL - NORMAL";
        if(_ataque_combo == Ataque_Normal_Fuerte)
            std::cout << "Ataque NORMAL - FUERTE";
        if(_ataque_combo == Ataque_Fuerte_Normal)
            std::cout << "Ataque FUERTE - NORMAL";
        if(_ataque_combo == Ataque_Fuerte_Fuerte)
            std::cout << "Ataque FUERTE - FUERTE";

        std::cout << std::endl;
    }
    
}

void Character::esquivar(uint16_t _direccion){
    if(esta_bloqueado() == false){
        set_accion(Accion_Dash);

        _objeto_motor->Dash(_direccion);
    }
    
}

void Character::saltar(){
    if(esta_bloqueado() == false){
        //set_accion(Saltar);
        _objeto_motor->saltar();
    }
}

void Character::mover(uint16_t _i_direccion){
    if(esta_bloqueado() == false){
            
        if(this->get_accion() == Nada){
            set_accion(Andar);
            _velocidad = _velocidadAndar;
        }
        else if(this->get_accion() == Andar){
            std::cout << "Andando" << std::endl;
            if(_velocidad<_velocidadAndar){
                _velocidad += 0.05;
            }
            if(accion_en_curso() == false){
                this->set_accion(Accion_Correr);
            }
        }
        else if(this->get_accion() == Accion_Correr){
            std::cout << "CORRIENDO" << std::endl;
            if(_velocidad<_velocidadCorrer){
                _velocidad += 0.1;
            }
        }
        _objeto_motor->VelocidadDireccion(_i_direccion,_velocidad,_tiempo->get_tiempo_desde_ultimo_update());
    }
}

bool Character::interactuar_con_objeto(){
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

    if(objeto_encontrado == true){
        set_accion(Accion_Interactuar);
    }

    return objeto_encontrado;
}

void Character::morir(){
    std::cout << "He muerto :("<< std::endl;
    setPositionXZ(10000, 10000);

}

Enum_Acciones Character::get_accion(){
    return _accion;
}

Enum_Tipo_Ataque Character::get_tipo_ataque(){
    return _tipo_ataque;
}

bool Character::esta_bloqueado(){
    if((_tiempo->get_current() - _tiempo_inicio_accion < _duracion_accion_actual) && _bloqueado == true){
        return true;
    }
    else{
        return false;
    }
}

bool Character::accion_en_curso(){
    if((_tiempo->get_current() - _tiempo_inicio_accion < _duracion_accion_actual)){
        return true;
    }
    else{
        return false;
    }
}

void Character::coger_arma(Arma* _arma){
    if(dynamic_cast<Arma_cerca*>(_arma) == NULL) {
        std::cout << "No es un arma cerca (es arma distancia)\n";
        _inventario->cambiar_objeto_distancia(static_cast<Arma_distancia*>(_arma));
    }
    else {
        std::cout << "Es un arma cerca\n";
         //_inventario->cambiar_objeto_cerca(_arma);
        _inventario->cambiar_objeto_cerca(static_cast<Arma_cerca*>(_arma));
    }
}

bool Character::intentar_recoger_arma() {
    std::vector<Arma*>* _armas = Game::game_instancia()->game_get_datos()->get_armas_manager()->get_armas();
   	Vector2 vec_player	= this->get_vector();
    Vector2 vec_cons = vec_player;

    uint8_t _size = (*_armas).size(); 
    std::cout << "Nº armas = " << (int)_size << "\n";
    for(uint8_t _i=0; _i<_size; _i++  ) {
        vec_cons	= (*_armas)[_i]->get_vector();
        if(comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_cons, 4)){
            coger_arma((*_armas)[_i]);
            
          //  _motor->haz_desaparecer(_id_motor);
            (*_armas)[_i]->haz_desaparecer();
            return true;
        }
    }
    
    return false;
}

///////////////////////////////////////////////////////// INICIO GESTION ACCIONES /////////////////////////////////////////////////////////

void Character::set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque){
    _tipo_ataque = _i_tipo_ataque;
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
        case Accion_Interactuar:
            return 1000;
        case Saltar:
            return 200;
        default:
            return 500;
    }
}

static bool getSiAccionBloqueaInput(Enum_Acciones _accion){
    switch(_accion)
    {
        case Accion_pre_atacar:
            return true;
        case Atacar:
            return true;
        case Accion_post_atacar:
            return true;
        case Accion_Dash:
            return true;
        case Accion_Interactuar:
            return true;
        case Saltar:
            return true;
        case Recibir_danyo:
            return true;
        default:
            return false;
    }
}

Enum_Tipo_Ataque Character::get_tipo_ataque_combo(Enum_Tipo_Ataque new_tipo_ataque){
    switch(_tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            if(new_tipo_ataque == Ataque_Normal)
                return Ataque_Normal_Normal;
            else if(new_tipo_ataque == Ataque_Fuerte)
                return Ataque_Normal_Fuerte;
        case Ataque_Fuerte:
            if(new_tipo_ataque == Ataque_Normal)
                return Ataque_Fuerte_Normal;
            else if(new_tipo_ataque == Ataque_Fuerte)
                return Ataque_Fuerte_Fuerte;
    }
}

void Character::set_accion(Enum_Acciones _i_accion){
    _accion = _i_accion;

    _tiempo_inicio_accion = _tiempo->get_current();
    _duracion_accion_actual = getTiempoAccion(_i_accion);

    _bloqueado = getSiAccionBloqueaInput(_i_accion);
    
    if(_bloqueado == false){ // No se bloquean inputs
        _objeto_motor->colorear_nodo(255,255,255);
    }
  
    if(_i_accion != Accion_pre_atacar && _i_accion != Accion_post_atacar && _i_accion != Atacar){
        set_tipo_ataque(Ataque_Ninguno);
    }
}

void Character::gestion_acciones(){
    gestion_ataque();
    gestion_dash();
    gestion_interactuar();
    gestion_saltar();
    gestion_recibir_danyado();
    //gestion_mover();
}

void Character::gestion_recibir_danyado(){
    if(get_accion() == Recibir_danyo){
        std::cout << "SIENDO DANYADO" << std::endl;
        _objeto_motor->colorear_nodo(255,0,0);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
            _objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_dash(){
    if(get_accion() == Accion_Dash){
        std::cout << "ESQUIVANDO" << std::endl;
        //_objeto_objeto_motor->colorear_nodo(0,255,0);
        //_objeto_motor->colorear_nodo(0,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
            _objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_saltar(){
    if(get_accion() == Saltar){
        std::cout << "SALTANDO" << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

void Character::gestion_interactuar(){
    if(get_accion() == Accion_Interactuar){
        std::cout << "Interactuando..." << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

void Character::gestion_ataque(){ // CONTROLAR GESTION DE ENEMIGO

    if(this->get_accion() == Accion_pre_atacar){
        std::cout << "PRE-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            
        }
    }
    else if(this->get_accion() == Atacar){

        Motor::Motor_GetInstance()->posicionar_ghost_ataque(_objeto_motor->getRigidBody());

        NPC_Manager * _npc_manager = Game::game_instancia()->game_get_datos()->get_npc_manager();
        NPC ** _npcs = _npc_manager->get_npcs();
        uint16_t _cont, _n_npcs;
        _n_npcs = _npc_manager->get_n_enemigos();

        for(_cont = 0; _cont < _n_npcs; _cont++) {
            if( //_npcs[_cont]->get_blackboard()->get_tipo_enemigo() != Aliado &&
                //Motor::Motor_GetInstance()->comprobar_colision_ataque(_npcs[_cont]->get_objeto_motor()->getRigidBody()) == true)
                comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _npcs[_cont]->get_vector(), 3) == true)
            {
                if(this->get_tipo_ataque() == Ataque_Normal){
                    _npcs[_cont]->danyar(_danyo_ataque_normal);
                }
                else if(this->get_tipo_ataque()  == Ataque_Fuerte){
                    _npcs[_cont]->danyar(_danyo_ataque_fuerte);
                }  
                else if(this->get_tipo_ataque()  == Ataque_Normal_Normal){
                    _npcs[_cont]->danyar(_danyo_ataque_normal);
                } 
                else if(this->get_tipo_ataque()  == Ataque_Normal_Fuerte){
                    _npcs[_cont]->danyar(_danyo_ataque_normal);
                } 
                else if(this->get_tipo_ataque()  == Ataque_Fuerte_Normal){
                    _npcs[_cont]->danyar(_danyo_ataque_normal);
                } 
                else if(this->get_tipo_ataque()  == Ataque_Fuerte_Fuerte){
                    _npcs[_cont]->danyar(_danyo_ataque_normal);
                } 
                std::cout << "----- " << _npcs[_cont]->get_vida() << "------" << std::endl;

                unsigned short direccion_ataque;
                direccion_ataque = lib_math_angulo_2_puntos(getX(), getZ(),_npcs[_cont]->getX(),_npcs[_cont]->getZ());
                std::cout <<direccion_ataque<< std::endl;
                
                _npcs[_cont]->get_objeto_motor()->Dash(direccion_ataque);
            }
        }
        std::cout << "ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(0,0,255);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_post_atacar);
        }
    }
    else if(this->get_accion() == Accion_post_atacar){
        std::cout << "POST-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,20,147);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

///////////////////////////////////////////////////////// FIN GESTION ACCIONES /////////////////////////////////////////////////////////

void Character::aumentar_danyo_ataque_fuerte(uint8_t _i_valor){
    _danyo_ataque_fuerte+=_i_valor;
}

void Character::aumentar_danyo_ataque_normal(uint8_t _i_valor){
    _danyo_ataque_normal+=_i_valor;
}

void Character::disminuir_danyo_ataque_fuerte(uint8_t _i_valor){
    _danyo_ataque_fuerte-=_i_valor;
}
void Character::disminuir_danyo_ataque_normal(uint8_t _i_valor){
    _danyo_ataque_normal-=_i_valor;
}

