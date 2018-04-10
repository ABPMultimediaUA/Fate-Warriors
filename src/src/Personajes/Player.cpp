#include "Player.h"

#include "../Input/Input.h"
#include "../Camara/Camara.h"
#include "../Tiempo/Time.h"
#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"

#include "../Nivel/Nivel.h"

#include "../Interfaz_Libs/Lib_Math.h"
#include "../Interfaz/Motor.h"
#include "../Zonas/Respawn.h"

#include "../Motor_sonido/Interfaz_sonido.h"

#include "../Datos_Partida.h"
#include "../Game.h"

#include "Cono_Vision.h"

#include <iostream>
                                                                                                            //  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input) : Character(_id, _i_x, _i_y, _i_z, 500, 0.4, 50, 75, Enum_Equipo_B)
                                                                {   
    _motor= Motor::Motor_GetInstance();
    _sonido= Interfaz_sonido::GetInstancia();
    //_tiempo = Time::Instance();
    //crear nodo de personaje del motor

    const char* cstr  = "models/Personajes/Jugador/Personaje.obj";

    _objeto_motor = new Objeto_Motor(this, E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,80);
    
    //_id_motor = _motor->crear_objeto(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);
    _motor->poner_camara_a_entidad(_objeto_motor);
    
    _cono_vision = new Cono_Vision(this);                                                            

    //std::cout<<"X player: "<<_motor->getX(_id_motor);
    //std::cout<<"Z player: "<<_motor->getZ(_id_motor)<<std::endl;

    _input = _i_input;
    _motor->set_text_vida(_vida);
    _especial = 0;
    //_sonido->Play_ambiente(2);
}    


Player::~Player(){
    delete _cono_vision;
}

void Player::update(){
    //std::cout<< "ACCION_ACTUAL: "<< _accion << "\n";
    if (_vida>0){

    gestion_acciones();
   // Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb_visor(_rb_apuntado, getPosicionRbAtaque(Ataque_Ninguno), btVector3(5,10,1), _direccion_actual);
    
    // Recoge si ha habido movimiento y la direccion de el mismo
    uint16_t _direccion;

    
    if(_input->get_mover(_direccion)){
        // Direccion buena con respecto de la camara
        int16_t _direccion_buena_2 = _direccion + Motor::Motor_GetInstance()->angulo_camara();
        while(_direccion_buena_2 >= 360) _direccion_buena_2 -= 360;
        while(_direccion_buena_2 < 0) _direccion_buena_2 += 360;

        uint16_t _direccion_buena = _direccion_buena_2;
        
        uint16_t _direccion_previa_movimiento = _direccion_buena;

       if(_cono_vision->get_apuntando() != nullptr) {
            mover_direccion(_direccion_buena, _cono_vision->get_rotacion_con_apuntando());
        }
        else {
            mover(_direccion_buena);
        }

        //s_sonido->Play_ambiente(2);
      
        if(_input->get_dash()){
            _sonido->Play_personaje(0);
          //  int16_t _direccion_incremento = (int16_t)_direccion_previa_movimiento-(int16_t)_direccion_posterior;
            //if(_direccion_incremento>-45 && _direccion_incremento<45){
               // _cono_vision->set_apuntando_a_objetivo_mas_proximo();
            //}
            
            esquivar(_direccion_buena); // Habra que pasar la direccion buena

                        _cono_vision->rotar_mirando_a_apuntando();

        }
    }

    if(_input->get_interactuar()){
        if(esta_bloqueado() == false){
            std::cout<< "Pulsa E\n";
            if(!interactuar_con_objeto()){
            std::cout<< "No encuentra objeto\n";
                intentar_recoger_arma();
            }
            //this->bloquear_input(1000);
            //std::cout<< "Interactuando..."<< std::endl;
        }
        else{
           // std::cout<< "No puede INTERACTUAR "<< std::endl;
        }
    }

    if(_input->get_centrar_camara()) {
       _motor->resetear_camara();
    }

    _cono_vision->update_direccion(_direccion_actual); 

    auto _cambio = _input->get_cambiar_arma();
    if(std::get<0>(_cambio)) {
        if(std::get<1>(_cambio))
            cambiar_arma_seleccionada_a_la_anterior();
        else
            cambiar_arma_seleccionada_a_la_siguiente();
    }

    auto _ataques = _input->get_atacar();

    if(std::get<0>(_ataques)) {
        if(std::get<1>(_ataques)) {    // Ataque especial
            atacar(Ataque_Especial);
            //std::cout << "Ataque Especial\n";
        }
        else if(std::get<2>(_ataques)){      // Ataque normal
            atacar(Ataque_Normal);
            _sonido->Play_personaje(1);
            //std::cout << "Ataque Normal\n";
            _cono_vision->preparar_ataque_objetivo_mas_proximo_con_impulso();
        }
        else {                          // Ataque fuerte
            this->atacar(Ataque_Fuerte);
            _sonido->Play_personaje(1);
            //std::cout << "Ataque Fuerte\n";
        }
    }
  

    if(_input->get_saltar()){
       // saltar();
        _cono_vision->set_apuntando_a_objetivo_mas_proximo();
       //_tiempobloqueo = _tiempo->get_current()+1000; BORRAME
	}

    if(esta_bloqueado() == false && !_input->get_mover(_direccion) && !_input->get_dash() && !_input->get_interactuar()
        && !std::get<0>(_ataques) && !_input->get_saltar() && _accion != Atacar && _accion != Saltar){
        set_accion(Nada);
    }
   
    //set level of detail del nivel
    Nivel* nivel=Nivel::nivel_instancia();
    nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));
    //std::cout << "id vertice set lod: " <<nivel->nivel_get_id_vertice(getX(),getZ()) << std::endl;
    }
    else{
        //std::cout<<"sigo muerto" << std::endl;
        //Respawn::posiciones_instancia()->comprobar_si_renace_y_renacer_personaje(this);

        Vector2 pos = Respawn::posiciones_instancia()->generar_posicion_del_bando(get_equipo());
        revivir(pos);
        Respawn::posiciones_instancia()->eliminar_character_a_reaparecer(this);
    }


}

void Player::gestion_dash(){
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


void Player::modificar_vida_en(short _i_vida){
	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida <= 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
    _motor->set_text_vida(_vida);
}

void Player::danyar(short _danyo){
    danyar_comun(_danyo);
    
    _motor->set_text_vida(_vida);
}

void Player::set_vida(short _i_vida){
	_vida=_i_vida;
    _motor->set_text_vida(_vida);
}

bool Player::puede_subir_especial(){
    if(_especial+1<3)
        return true;
    return false;
}

void Player::aumentar_especial(){
    _especial+=1;
}

void Player::disminuir_especial(){
    _especial-=1;
}