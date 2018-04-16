#include "Cono_Vision.h"

#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"

#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Interfaz_Libs/Lib_Math.h"

#include "Character.h"


Cono_Vision::Cono_Vision(Character* _i_asociado) : _asociado(_i_asociado), _personaje_fijado(nullptr) {
	_visor = Motor::Motor_GetInstance()->crear_rb_vision();
	_tamanyocono = new btVector3(5,10,1);
}

Cono_Vision::~Cono_Vision() {
    Motor::Motor_GetInstance()->borrar_rb(_visor);
	delete _tamanyocono;
}


void Cono_Vision::update_direccion(uint16_t _direccion){


    if(_personaje_fijado!=nullptr){
        if(_personaje_fijado->get_vida_actual()<1 || get_distancia_con_apuntado()>60){
            _personaje_fijado = nullptr;
        }
        else{
            
            _direccion = get_rotacion_con_apuntando();
        }
    }
    
	    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb_visor(_visor, get_posicion_para_el_cono(), *_tamanyocono, _direccion);
}

/*Obtencion del enemigos mas proximo*/

void Cono_Vision::rotar_en_funcion_de_un_character(Character* _objetivo){
    uint16_t angulo_giro = get_rotacion_con_objetivo(_objetivo);

    _asociado->set_direccion_actual(angulo_giro);
    _asociado->rotar_cuerpo(angulo_giro);
}

float Cono_Vision::get_distancia_con_apuntado(){
    return get_distancia_con_un_character(_personaje_fijado);
}

float Cono_Vision::get_distancia_con_un_character(Character* enemigo){
   return lib_math_distancia_2_puntos(enemigo->getX(), enemigo->getZ(), _asociado->getX(), _asociado->getZ());
}


uint16_t Cono_Vision::get_rotacion_con_objetivo(Character* _objetivo){
    
	uint16_t angulo_giro = lib_math_angulo_2_puntos(_asociado->getX(), _asociado->getZ(), _objetivo->getX(), _objetivo->getZ());

    float _cos, _sen;
    _cos = sin(angulo_giro*std::acos(-1)/180);
    _sen = cos(angulo_giro*std::acos(-1)/180);

    // Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
    int16_t _nueva_direccion_2 = atan2(_sen, _cos) * 180 / std::acos(-1);
    while(_nueva_direccion_2 >= 360) _nueva_direccion_2 -= 360;
    while(_nueva_direccion_2 < 0) _nueva_direccion_2 += 360;

    uint16_t _nueva_direccion = _nueva_direccion_2;

    return _nueva_direccion;
}

uint16_t Cono_Vision::get_rotacion_con_apuntando(){
    get_rotacion_con_objetivo(_personaje_fijado);
}



void Cono_Vision::preparar_ataque_objetivo_mas_proximo_con_impulso(){

    Character* enemigo = objetivo_mas_proximo_angulo();
    
	if(enemigo!=nullptr){
        float distance = get_distancia_con_un_character(enemigo);

        if (distance>6){
            _asociado->get_objeto_motor()->Impulso(_asociado->get_direccion_actual(), 9000);
        }
    }
}

void Cono_Vision::impulso_hacia_apuntando(){
    if(_personaje_fijado!=nullptr){
        uint16_t direccion = _asociado->get_direccion_actual()+180;
        if (direccion>360) direccion-=360;
       _asociado->get_objeto_motor()->Impulso(direccion, 19000);
    }
}

void Cono_Vision::rotar_mirando_a_apuntando(){
   if(_personaje_fijado!=nullptr){
           rotar_en_funcion_de_un_character(_personaje_fijado);
    }
}

Character* Cono_Vision::objetivo_mas_proximo_angulo(){

    if(_personaje_fijado != nullptr){
        rotar_en_funcion_de_un_character(_personaje_fijado);
        return _personaje_fijado;
    }

    Datos_Partida * _datos_partida = Game::game_instancia()->game_get_datos();
    Character ** _characters = _datos_partida->get_characters();
    uint16_t _num_characters  = _datos_partida->get_num_characters();
    Character * enemigo = nullptr;

    float distance = 9999;
    float distance_aux = 9999;

    for(uint16_t _cont = 0; _cont < _num_characters; _cont++) {
      if( _characters[_cont]!=_asociado &&  Motor::Motor_GetInstance()->comprobar_colision(_visor, _characters[_cont]->get_objeto_motor()->getRigidBody()) == true){
          distance_aux = get_distancia_con_un_character(_characters[_cont]);
          if(distance_aux<distance){
            distance = distance_aux;
            enemigo = _characters[_cont];
          }
      }
    }           

    if(enemigo!=nullptr){
        rotar_en_funcion_de_un_character(enemigo);
        return enemigo;
    }
    else {
        return enemigo;
    }
}


/*Calcula la posicion sobre la que se colocara el cono*/

btVector3 Cono_Vision::get_posicion_para_el_cono(){
	float x_atacante = _asociado->getX();
    float y_atacante = _asociado->getY();
    float z_atacante = _asociado->getZ();
    float _cos, _sen;


    if(_personaje_fijado!=nullptr){
        _cos = cos(get_rotacion_con_apuntando()*std::acos(-1)/180);
        _sen = sin(get_rotacion_con_apuntando()*std::acos(-1)/180);
    }
    else{
        _cos = cos(_asociado->get_direccion_actual()*std::acos(-1)/180);
        _sen = sin(_asociado->get_direccion_actual()*std::acos(-1)/180);
    }

	return btVector3(x_atacante + _sen * 9, y_atacante, z_atacante + _cos * 9);
}


/* Metodo set */
void Cono_Vision::set_apuntando_a_objetivo_mas_proximo(){
    if(_personaje_fijado!=nullptr){
        _personaje_fijado = nullptr;
    }
    else{
       _personaje_fijado = objetivo_mas_proximo_angulo();
    }
}


Character* Cono_Vision::get_apuntando(){
    return _personaje_fijado;
}