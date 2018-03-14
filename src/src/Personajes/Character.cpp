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
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Consumibles/Consumible_Power_Up.h"
#include "../Interruptor.h"
#include "../Respawn.h"



Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte, Enum_Equipo _i_equipo) 
    :Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad),
    _danyo_ataque_normal(_i_danyo_ataque_normal), _danyo_ataque_fuerte(_i_danyo_ataque_fuerte),_tiene_arma_corta(false),
    _tiene_arma_larga(false) {

    _inmortal = false;
    _inventario = new Inventario();
    _tiempo = Time::Instance();
    _accion = Nada;
    _tipo_ataque = Ataque_Ninguno;
    _tiempo_inicio_accion = 0;
    _duracion_accion_actual = 0;
    _velocidadAndar = _i_velocidad;
    _velocidadCorrer = _i_velocidad * 2;
    _rb_ataque = Motor::Motor_GetInstance()->crear_rb_ataque();
    _equipo = _i_equipo;
    _bloqueado = false;
    _npcs_persiguiendome = 0;
    
}

Character::~Character() {
    delete _inventario;
    Motor::Motor_GetInstance()->borrar_rb(_rb_ataque);
    Game::game_instancia()->get_consumibles_action()->borrar_power_up(_power_up);
}

int16_t Character::get_vida(){
	return _vida;
}

void Character::anyadir_power_up(Consumible_Power_Up* _i_power_up){
    if(_power_up!=nullptr){
        _power_up = _i_power_up;
    }  
}

Enum_Equipo Character::get_equipo(){
    return _equipo;
}

void Character::eliminar_power_up_puntero(){
        _power_up=nullptr;
}

void Character::activar_inmunidad_a_danyos(){
    _inmortal = true;
}

void Character::desactivar_inmunidad_a_danyos(){
    _inmortal = false;
}

void Character::modificar_vida_en(short _i_vida){

	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida <= 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
}

void Character::danyar_comun(short _danyo){

    if(!_inmortal){
        _vida = _vida - _danyo;

        if(_accion == Accion_pre_atacar){
            //std::cout << "Ataque cortado" << std::endl;
        }

        set_accion(Recibir_danyo);

        if(_vida <= 0){
            morir();
        }
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
    if(_accion == Saltar && (_i_tipo_ataque == Ataque_Normal || _i_tipo_ataque == Ataque_Fuerte)){
        _i_tipo_ataque = Ataque_Salto;
        std::cout << "ATAQUE CON SALTO"<< std::endl;
    }

    if(
        this->get_tipo_ataque() == Ataque_Ninguno && esta_bloqueado() == false && 
        (
            _accion != Saltar ||
            _accion == Saltar && _i_tipo_ataque == Ataque_Salto
        )
        ){

        this->set_tipo_ataque(_i_tipo_ataque);
        this->set_accion(Accion_pre_atacar);
    }
    else if(
            _accion == Accion_post_atacar && _tipo_ataque != Ataque_Salto && _tipo_ataque != Ataque_Especial && _tipo_ataque != Ataque_Normal_Normal 
            && _tipo_ataque != Ataque_Normal_Fuerte && _tipo_ataque != Ataque_Fuerte_Normal && _tipo_ataque != Ataque_Fuerte_Fuerte &&
                (
                    (_inventario->get_tipo_arma() != Tipo_Arma_distancia) ||
                    (_inventario->get_tipo_arma() == Tipo_Arma_distancia && _i_tipo_ataque != Ataque_Normal)
                )
            ) {
                
        Enum_Tipo_Ataque _ataque_combo;
        _ataque_combo = get_tipo_ataque_combo(_i_tipo_ataque);

        set_accion(Accion_pre_atacar);
        set_tipo_ataque(_ataque_combo);

        /*
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
        */
    }
    
}

void Character::esquivar(uint16_t _direccion){
    if(esta_bloqueado() == false){
        set_accion(Accion_Dash);

        //_objeto_motor->Dash(_direccion);
    }
    
}

void Character::saltar(){
    if(esta_bloqueado() == false && _accion != Saltar){
        set_accion(Saltar);
        _objeto_motor->saltar();
    }
}

void Character::mover(uint16_t _i_direccion){
    if(esta_bloqueado() == false){

        _direccion_actual = _i_direccion;
            
        if(this->get_accion() == Nada){
            set_accion(Andar);
            _velocidad = _velocidadAndar;
        }
        else if(this->get_accion() == Andar){
            //std::cout << "Andando" << std::endl;
            if(_velocidad<_velocidadAndar){
                _velocidad += 0.05;
            }
            if(accion_en_curso() == false){
                this->set_accion(Accion_Correr);
            }
        }
        else if(_accion == Accion_Correr){
            //std::cout << "CORRIENDO" << std::endl;
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

    Interruptor** _interruptores = _int_man->get_interruptores();
    unsigned short n_interruptores = _int_man->get_n_interruptores();


    unsigned short _cont;
    bool objeto_encontrado = false;

    //Busca palancas y la usa 

    for(_cont = 0; _cont < n_interruptores && objeto_encontrado == false; _cont++) {
		if( comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _interruptores[_cont]->get_vector(), 3) == true){
            // Encuentra palanca e intenta accionarla
            
            _interruptores[_cont]->set_activado(true);
            objeto_encontrado = true;
            std::cout << "Usa palanca"<< std::endl;
        }
	}




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

                    _puertas[_cont]->set_abierta();
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
    //float mult = 4.9212625;
    //std::cout << "He muerto :("<< std::endl;
    _inventario->soltar_armas(getX(), getZ()); 

    Respawn::posiciones_instancia()->anyadir_character_y_tiempo_para_reaparecer(this, _tiempo->get_current()+9000);
    setY(99999999999);

}


void Character::revivir(Vector2 pos){
    set_vida(_vida_maxima);
    _npcs_persiguiendome = 0;
    setPositionXZ(pos._x, pos._y);
    setY(0);
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


/////////////////////////////////////////////////// GESTION DE ARMAS ///////////////////////////////////////


void Character::coger_arma(Arma* _arma){
    if(dynamic_cast<Arma_cerca*>(_arma) == NULL) {
        //std::cout << "No es un arma cerca (es arma distancia)\n";
        _inventario->cambiar_objeto_distancia(static_cast<Arma_distancia*>(_arma));
    }
    else {
        //std::cout << "Es un arma cerca\n";
         //_inventario->cambiar_objeto_cerca(_arma);
        _inventario->cambiar_objeto_cerca(static_cast<Arma_cerca*>(_arma));
    }
}

bool Character::intentar_recoger_arma() {
    std::vector<Arma*>* _armas = Game::game_instancia()->game_get_datos()->get_armas_manager()->get_armas();
   	Vector2 vec_player	= this->get_vector();
    Vector2 vec_cons = vec_player;

    for(uint8_t _i=0; _i<(*_armas).size(); _i++  ) {
        vec_cons	= (*_armas)[_i]->get_vector();
        if((*_armas)[_i]->get_ocupada()==false && comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_cons, 4)){
            (*_armas)[_i]->setPositionXZ(99999,9999);
            coger_arma((*_armas)[_i]);
          //  _motor->haz_desaparecer(_id_motor);
            return true;
        }
    }
    
    return false;
}

void Character::cambiar_arma_seleccionada_a_la_anterior(){
    _inventario->cambiar_arma_seleccionada_a_la_anterior();
}

void  Character::cambiar_arma_seleccionada_a_la_siguiente(){
    _inventario->cambiar_arma_seleccionada_a_la_siguiente();
}



///////////////////////////////////////////////////////// INICIO GESTION ACCIONES /////////////////////////////////////////////////////////

void Character::set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque){
    _tipo_ataque = _i_tipo_ataque;
}

void Character::impulso_danyar(Character * atacante, Character * atacado, int impulso){

    float x = atacado->getX() - atacante->getX();
    float z = atacado->getZ() - atacante->getZ();

    Vector2 direccion_impulso(x,z);
    direccion_impulso.Normalize();

    float valor = lib_math_distancia_2_puntos(atacado->getX(), atacado->getZ(), atacante->getX(), atacante->getZ());

    Vector3 a(direccion_impulso._x*(impulso/valor),0,direccion_impulso._y*(impulso/valor));
    atacado->get_objeto_motor()->Impulso_explosion(a);

}


int Character::getTiempoAccion(Enum_Acciones _accion){

    Tipo_Arma tipo_arma = _inventario->get_tipo_arma();
    Enum_Nombre_Arma nombre_arma = _inventario->get_nombre_arma();

    if(_accion == Accion_pre_atacar){

        if(tipo_arma == Tipo_Arma_distancia && _tipo_ataque == Ataque_Normal){
            return 1;
        }
        else if(tipo_arma == Tipo_Arma_cerca){

            if(nombre_arma == Nombre_Arma_Katana){

                if(_tipo_ataque == Ataque_Normal){
                    return 150;
                }
                else if(_tipo_ataque == Ataque_Fuerte){
                    return 250;
                }
                else if(_tipo_ataque == Ataque_Salto){
                    return 200;
                }
                else if(_tipo_ataque == Ataque_Especial){
                    return 200;
                }
                else{
                    std::cout<< "No debe entrar 1 \n";
                    return 200;
                }   
            }

        }
        else if(_tipo_ataque == Ataque_Normal){
            return 150;
        }
        else if(_tipo_ataque == Ataque_Fuerte){
            return 250;
        }
        else if(_tipo_ataque == Ataque_Salto){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Especial){
            return 200;
        }
        else{
            std::cout<< "No debe entrar 2 \n";
            return 200;
        }
            
    }
    
    else if(_accion == Atacar){
        return 1;
    }

    else if(_accion == Accion_post_atacar){

        if(tipo_arma == Tipo_Arma_distancia && _tipo_ataque == Ataque_Normal){
            return 1;
        }
        else if(tipo_arma == Tipo_Arma_cerca){

            if(nombre_arma == Nombre_Arma_Katana){

                if(_tipo_ataque == Ataque_Normal){
                    return 150;
                }
                else if(_tipo_ataque == Ataque_Fuerte){
                    return 250;
                }
                else if(_tipo_ataque == Ataque_Salto){
                    return 200;
                }
                else if(_tipo_ataque == Ataque_Especial){
                    return 200;
                }
                else{
                    //std::cout<< "No debe entrar 3 \n";
                    return 200;
                }
                    
            }
        }
        else if(_tipo_ataque == Ataque_Normal){
            return 150;
        }
        else if(_tipo_ataque == Ataque_Fuerte){
            return 250;
        }
        else if(_tipo_ataque == Ataque_Salto){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Especial){
            return 200;
        }
        else
            return 500;
    }
    else if(_accion == Accion_Dash){
        return 200;
    }
    else if(_accion == Accion_Interactuar){
        return 25;
    }
    else if(_accion == Saltar){
        return 600;
    }
    else{
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
            return false;
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
            else
                std::cout<< "No debe entrar 4.0 \n";
            
        case Ataque_Fuerte:
            if(new_tipo_ataque == Ataque_Normal)
                return Ataque_Fuerte_Normal;
            else if(new_tipo_ataque == Ataque_Fuerte)
                return Ataque_Fuerte_Fuerte;
            else
                std::cout<< "No debe entrar 4.1 \n";
        default:
            std::cout<< "No debe entrar 4.2 \n";
            return Ataque_Fuerte_Fuerte;
    }
}

uint8_t Character::get_danyo_ataque(Enum_Tipo_Ataque tipo_ataque){
    switch(tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            return _danyo_ataque_normal;
        case Ataque_Fuerte:
            return _danyo_ataque_fuerte;
        default:
            return _danyo_ataque_normal;
    }
}

int Character::get_impulso_danyar(Enum_Tipo_Ataque tipo_ataque){
    switch(tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            return 15000;
        case Ataque_Fuerte:
            return 30000;
        default:
            return 25000;
    }
}

btVector3 Character::getPosicionRbAtaque(Enum_Tipo_Ataque _ataque){

    float x_atacante = this->getX();
    float y_atacante = this->getY();
    float z_atacante = this->getZ();
    float _cos, _sen;
    _cos = cos(_direccion_actual*std::acos(-1)/180);
    _sen = sin(_direccion_actual*std::acos(-1)/180);
  
    switch(_ataque)
    {
        default:
            return btVector3(x_atacante + _sen * 3, y_atacante, z_atacante + _cos * 3);
    }
}

btVector3 Character::getEscalaRbAtaque(Enum_Tipo_Ataque _ataque){
    // ancho, alto, largo
    Tipo_Arma tipo_arma = _inventario->get_tipo_arma();
    Enum_Nombre_Arma nombre_arma = _inventario->get_nombre_arma();


    if(tipo_arma == Tipo_Arma_cuerpo_a_cuerpo){

        if(_tipo_ataque == Ataque_Normal){
            //std::cout<< "cuerpo a cuerpo normal" <<std::endl;
            return btVector3(2,1,2);
        }
        else if(_tipo_ataque == Ataque_Fuerte){
            //std::cout<< "cuerpo a cuerpo  fuerte" <<std::endl;
            return btVector3(2.5,1,2);
        }
        else if(_tipo_ataque == Ataque_Salto){
            //std::cout<< "cuerpo a cuerpo salto" <<std::endl;
            return btVector3(2,1,2);
        }
        else if(_tipo_ataque == Ataque_Especial){
            //std::cout<< "cuerpo a cuerpo Especial" <<std::endl;
            return btVector3(2,1,2);
        }
        else
            return btVector3(2,1,2);
    }
    else if(tipo_arma == Tipo_Arma_cerca){

        if(nombre_arma == Nombre_Arma_Katana){

            if(_tipo_ataque == Ataque_Normal){
                //std::cout<< "KATANA normal" <<std::endl;
                return btVector3(2,1,2);
            }
            else if(_tipo_ataque == Ataque_Fuerte){
                //std::cout<< "KATANA fuerte" <<std::endl;
                return btVector3(2.5,1,2);
            }
            else if(_tipo_ataque == Ataque_Salto){
                //std::cout<< "KATANA salto" <<std::endl;
                return btVector3(2,1,2);
            }
            else if(_tipo_ataque == Ataque_Especial){
                //std::cout<< "KATANA especial" <<std::endl;
                return btVector3(2,1,2);
            }
            else
                return btVector3(2,1,2);
        }
    }
    else{
        //std::cout<< "Escala RB ATAQUE default" <<std::endl;
        return btVector3(5,1,5);
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
    if(get_accion() == Recibir_danyo && !_inmortal){
        //std::cout << "SIENDO DANYADO" << std::endl;
        _objeto_motor->colorear_nodo(255,0,0);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
            _objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_dash(){
    if(get_accion() == Accion_Dash){
        //std::cout << "ESQUIVANDO" << std::endl;
        _objeto_motor->Dash(_direccion_actual);
        //_objeto_objeto_motor->colorear_nodo(0,255,0);
        //_objeto_motor->colorear_nodo(0,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_Correr);
            _objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_saltar(){
    if(get_accion() == Saltar){
        std::cout << "SALTANDO" << std::endl;

        if(accion_en_curso() == false){
            std::cout << "FIN SALTO" << std::endl;
            this->set_accion(Accion_Correr);
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

void Character::gestion_ataque(){ // CONTROLAR GESTION DE ENEMIGO, que esta OVERRIDE

    if(this->get_accion() == Accion_pre_atacar){
        //std::cout << "PRE-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            Tipo_Arma tipo_arma = _inventario->get_tipo_arma();
            if(_tipo_ataque == Ataque_Especial || _tipo_ataque == Ataque_Fuerte || tipo_arma == Tipo_Arma_cuerpo_a_cuerpo || tipo_arma ==Tipo_Arma_cerca){
                Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb_ataque, getPosicionRbAtaque(_tipo_ataque), getEscalaRbAtaque(_tipo_ataque), _direccion_actual);
            }
        }
    }
    else if(this->get_accion() == Atacar){

        Tipo_Arma tipo_arma = _inventario->get_tipo_arma();

        if(_tipo_ataque == Ataque_Especial || _tipo_ataque == Ataque_Fuerte || tipo_arma == Tipo_Arma_cuerpo_a_cuerpo || tipo_arma ==Tipo_Arma_cerca){

            Datos_Partida * _datos_partida = Game::game_instancia()->game_get_datos();
            Character ** _characters = _datos_partida->get_characters();
            uint16_t _cont, _num_characters;
            _num_characters = _datos_partida->get_num_characters();

            bool golpea = false;

            for(_cont = 0; _cont < _num_characters; _cont++) {
                if( _characters[_cont]->get_vida_actual()>0 && _characters[_cont]->get_equipo() != _equipo &&
                    Motor::Motor_GetInstance()->comprobar_colision(_rb_ataque, _characters[_cont]->get_objeto_motor()->getRigidBody()) == true)
                {
                    _characters[_cont]->danyar(get_danyo_ataque(this->get_tipo_ataque()));
            
                    //std::cout << "----- " << _characters[_cont]->get_vida() << "------" << std::endl;

                    // Impulsa al atacado
                    impulso_danyar(this, _characters[_cont], get_impulso_danyar(_tipo_ataque));

                    golpea = true;
                }
            }

            if(golpea == true && tipo_arma == Tipo_Arma_cerca){
                Arma_cerca * arma = _inventario->get_objeto_cerca();
                arma->decrementar_usos();
                _inventario->borrar_si_se_puede(arma);
            }
            _objeto_motor->Impulso(_direccion_actual, 3000);
        }
        else if(tipo_arma == Tipo_Arma_distancia){
            Character * atacado = _inventario->usar(_objeto_motor, _direccion_actual);
            Arma_distancia* _arma_usada = _inventario->get_objeto_distancia();
            
            if(atacado != 0){
                atacado->danyar(_arma_usada->get_danyo());
                impulso_danyar(this, atacado, _arma_usada->get_impulso());
            }
        }

        //std::cout << "ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(0,0,255);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_post_atacar);
        }
    }
    else if(this->get_accion() == Accion_post_atacar){
        //std::cout << "POST-ATACANDO" << std::endl;
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

uint16_t Character::get_direccion_actual(){
    return _direccion_actual;
}

void Character::set_direccion_actual(uint16_t nueva_direccion){
    _direccion_actual = nueva_direccion;
}


void Character::rotar_cuerpo(uint16_t _i_valor){
    _objeto_motor->rotar_nodo(_i_valor);
}