#include "Zona.h"

#include "../Interfaz/Motor.h"
#include "../Personajes/Character.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Player.h"
#include "../Datos_Partida.h"
#include "../Interfaz/Motor.h"
#include "../Game.h"
#include "../Tiempo/Time.h"
#include "../Interactuables/Interruptor.h"
#include "../Interactuables/Puerta_Pincho.h"

Zona::Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y){
_reloj=Time::Instance();
    _rb = Motor::Motor_GetInstance()->crear_rb_ataque();
    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb,btVector3(_i_x,_i_y,_i_z), btVector3(long_x,10,long_y), 0);

    _long_x = long_x;
    _long_y = long_y;
    _pos_x = _i_x;
    _pos_y = _i_z;

    _npcs_persiguiendome = 0;
}

Zona::~Zona() {
    Motor::Motor_GetInstance()->borrar_rb(_rb);
    _interruptores_asociados.clear();
    std::cout<<"borrado de zona"<<std::endl;
}


/*METODO PARA ACTUALIZAR LA ZONA*/

void Zona::actualizar_zona(){
  
}


float Zona::distancia_player_a_zona(){
        Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Player* _player = _datos->get_player();
   return lib_math_distancia_2_puntos(_player->getX(), _player->getZ(), _pos_x, _pos_y);
}


bool Zona::esta_jugador_en_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Player* _player = _datos->get_player();
    Motor* motor = Motor::Motor_GetInstance();

    if(motor->comprobar_colision(_rb, _player->get_objeto_motor()->getRigidBody()) == true){
        return true;
    }
    return false;
}

uint8_t Zona::get_num_npc_en_zona(){
    
    uint8_t num_npc = 0;

    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();


    for (uint16_t num_character=0; num_character<_num_characters-1; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            num_npc++;
       }   
    }
    return num_npc;

}

void Zona::restaurar_vida_enemigos_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();


    for (uint16_t num_character=0; num_character<_num_characters-1; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            todos_personajes[num_character]->set_vida(todos_personajes[num_character]->get_vida_maxima());
       }   
    }
}


/* ASOCIAR ELEMENTOS A LA ZONA */ 
void Zona::set_interruptor_asociado(Interruptor* _i_interruptor){
    _interruptores_asociados.push_back(_i_interruptor);
}

void Zona::set_puerta_pincho_asociada(Puerta_Pincho* _i_puerta_pincho){
    _puerta_pincho_asociados.push_back(_i_puerta_pincho);
}

std::vector<Interruptor*> Zona::get_interruptores_asociados(){
    return _interruptores_asociados;
}


/* METODOS DE CERRAR/ABRIR ELEMENTOS ASOCIADOS*/ 

void Zona::activar_todas_las_puerta_pincho(){
    uint8_t num_interruptores = _puerta_pincho_asociados.size();
    for (uint8_t cont=0; cont<num_interruptores; cont++){
       _puerta_pincho_asociados[cont]->activar();
    }
}

void Zona::desactivar_todas_las_puerta_pincho(){
    uint8_t num_interruptores = _puerta_pincho_asociados.size();
    for (uint8_t cont=0; cont<num_interruptores; cont++){
       _puerta_pincho_asociados[cont]->desactivar();
    }
}