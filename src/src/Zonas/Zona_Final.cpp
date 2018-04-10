#include "Zona_Final.h"

#include "../Interfaz/Motor.h"
#include "../Personajes/Character.h"
#include "../Datos_Partida.h"
#include "../Interfaz/Motor.h"
#include "../Game.h"
#include "../Tiempo/Time.h"


Zona_Final::Zona_Final(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo) : Zona(_i_x, _i_y, _i_z, long_x, long_y, i_equipo){
/*
_reloj=Time::Instance();
    _equipo = i_equipo;
    _rb = Motor::Motor_GetInstance()->crear_rb_ataque();
    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb,btVector3(_i_x,_i_y,_i_z), btVector3(long_x,10,long_y), 0);
    _conquistando = false;
    _tiempo_inicio_conquista = 0;
    _pos_x = _i_x;
    _pos_y = _i_z;
    _tiempo_restante_conquista = 10000;

    _npcs_persiguiendome = 0;
    */
}

Zona_Final::~Zona_Final() {

}


/*Metodo para actualizar los valores de la zona*/

void Zona_Final::actualizar_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();

    if(esta_jugador_en_zona()){
        for (uint16_t num_character=0; num_character<_num_characters; num_character++){
            if(motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
               // personajes_de_la_zona.push_back(todos_personajes[num_character]);
               game->cambio_a_update_win();
            }   
        }
   
    }



}