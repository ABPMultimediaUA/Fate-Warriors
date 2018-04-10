#include "Zona_Respawn_Infinito.h"

#include "Respawn.h"

#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"
#include "../Personajes/Player.h"


Zona_Respawn_Infinito::Zona_Respawn_Infinito(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo, uint16_t num_enemigos, float _i_distancia) : Zona(_i_x, _i_y, _i_z, long_x, long_y, i_equipo){
    _num_enemigos = num_enemigos;
    _distancia_reaparecer = _i_distancia;
   Respawn* _respawn = Respawn::posiciones_instancia();
   _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, true, this);
}

Zona_Respawn_Infinito::~Zona_Respawn_Infinito() {

}

/*Metodo para actualizar los valores de la zona*/

void Zona_Respawn_Infinito::actualizar_zona(){
    
comprobar_si_reaparecer_npcs();
}



void Zona_Respawn_Infinito::comprobar_si_reaparecer_npcs(){
    if(!esta_jugador_en_zona() && distancia_player_a_zona() > _distancia_reaparecer){
        Respawn* _respawn = Respawn::posiciones_instancia();
        int16_t num_a_reaparecer = _num_enemigos - get_num_npc_en_zona();
        restaurar_vida_enemigos_zona();
       _respawn->revivir_enemigos_en_zona(num_a_reaparecer, _pos_x, _pos_y, true, this);
    }
}

