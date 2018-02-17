#include "Zona.h"
#include "Interfaz/Motor.h"
#include "Personajes/Character.h"
#include "Datos_Partida.h"
#include "Interfaz/Motor.h"
#include "Game.h"
#include "Tiempo/Time.h"


Zona::Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo){
_reloj=Time::Instance();
    _equipo = i_equipo;
    _rb = Motor::Motor_GetInstance()->crear_rb_ataque();
    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb,btVector3(_i_x,_i_y,_i_z), btVector3(long_x,10,long_y), 0);
    _conquistando = false;
    _tiempo_inicio_conquista = 0;
    _pos_x = _i_x;
    _pos_y = _i_z;
}

Zona::~Zona() {
    Motor::Motor_GetInstance()->borrar_rb(_rb);
}


void Zona::actualizar_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();

    personajes_de_la_zona.clear();
    _num_characters_equipo_A = 0;
    _num_characters_equipo_B = 0;
    bool _conquistando_aux=true;

    for (uint16_t num_character=0; num_character<_num_characters; num_character++){
       if(motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            personajes_de_la_zona.push_back(todos_personajes[num_character]);
            //std::cout << this <<  " estoy en la zona \n";

            if(todos_personajes[num_character]->get_equipo() == Enum_Equipo_A){
                _num_characters_equipo_A++;
            }
            else{
                _num_characters_equipo_B++;
            }

            if(todos_personajes[num_character]->get_equipo() == _equipo){
                _conquistando = false;
                _conquistando_aux = false;
            }
       }   
    }

    if(personajes_de_la_zona.size() == 0){
        _conquistando = false;
        _conquistando_aux = false;
    }

    if(_conquistando_aux && !_conquistando){
        _conquistando = true;
        iniciar_tiempo_conquista();
    }


    if(_conquistando){
       //std::cout << " conquistando.... \n";
    }

    if(_conquistando && _reloj->get_current() >_tiempo_inicio_conquista+5000){
        std::cout<< " conquistado!!!!'------------------------------------------ \n";
        cambiar_bando();
    }

}


void Zona::cambiar_bando(){
    _equipo=personajes_de_la_zona[0]->get_equipo();
    _conquistando=false;
}

void Zona::iniciar_tiempo_conquista(){
    _tiempo_inicio_conquista = _reloj->get_current();
}

std::vector <Character*> Zona::get_characters(){
    return personajes_de_la_zona;
}