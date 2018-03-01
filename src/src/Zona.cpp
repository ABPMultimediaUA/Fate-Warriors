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
    _tiempo_restante_conquista = 30000;
}

Zona::~Zona() {
    Motor::Motor_GetInstance()->borrar_rb(_rb);
}


/*Metodo para actualizar los valores de la zona*/

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
    bool _pausar_conquista = false;


    for (uint16_t num_character=0; num_character<_num_characters; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            personajes_de_la_zona.push_back(todos_personajes[num_character]);
            //std::cout << this <<  " estoy en la zona \n";

            if(todos_personajes[num_character]->get_equipo() == Enum_Equipo_A){
                _num_characters_equipo_A++;
            }
            else{
                _num_characters_equipo_B++;
            }

            if(todos_personajes[num_character]->get_equipo() == _equipo){
                _conquistando_aux = false;
                _pausar_conquista = true;
            }
       }   
    }

    //Si no hay del bando que toca tambien debe de restaurarse
    if(!hay_personajes_conquistando_esta_zona()){
         _conquistando = false;
      //  _conquistando_aux = false;
        _tiempo_restante_conquista = 30000;
    }

    else{                               //hay personajes conquistando
        if(!_conquistando){             //Es la primera vez que se pone a conquistar el territorio se debe poner el tiempo
            if(_conquistando_aux){
                _conquistando = true;
                iniciar_tiempo_conquista();
            }
        }

        else{                           //No es la primera vez que se conquista, se estaba conquistando de antes
            if(_pausar_conquista){
                _conquistando = false;
                set_tiempo_restante_para_conquistar();
            }

            if(_conquistando){
                //std::cout << _tiempo_restante_conquista - (_reloj->get_current() - _tiempo_inicio_conquista) << " conquistando.... \n";
            }

            //Si se esta conquistando debe comprobar si ha pasado el tiempo necesario de conquista
            if(_reloj->get_current() >_tiempo_inicio_conquista+_tiempo_restante_conquista){
                //std::cout<< " conquistado!!!!'------------------------------------------ \n";
                _tiempo_restante_conquista = 0;
                cambiar_bando();
            }
        }


        //Si esta conquistando y de golpe entra un enemigo debe pausar el tiempo de conquista y guardar el tiempo que falta para conquistar el territorio

    }

}

//Comprobar si hay personajes conquistando
bool Zona::hay_personajes_conquistando_esta_zona(){
    if(_equipo != Enum_Equipo_A && _num_characters_equipo_A==0){
        return false;
    }

    else if(_equipo != Enum_Equipo_B && _num_characters_equipo_B==0){
        return false;
    }
    return true;
}


//Pausa el tiempo que necesita para conquistar un territorio
void Zona::set_tiempo_restante_para_conquistar(){
    _tiempo_restante_conquista = _tiempo_restante_conquista - (_reloj->get_current() - _tiempo_inicio_conquista);
    std::cout << _tiempo_restante_conquista << "Tiempo_que queda" << std::endl;
}

//Cambia de bando el equipo la zona
void Zona::cambiar_bando(){
    _equipo=personajes_de_la_zona[0]->get_equipo();
    _conquistando=false;
}

//Restaura el tiempo de conquista
void Zona::iniciar_tiempo_conquista(){
    _tiempo_inicio_conquista = _reloj->get_current();
}

std::vector <Character*> Zona::get_characters(){
    return personajes_de_la_zona;
}

bool Zona::get_conquistando(){
    return _conquistando;
}