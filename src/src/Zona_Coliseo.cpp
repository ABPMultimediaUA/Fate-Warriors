#include "Zona_Coliseo.h"
#include "Interfaz/Motor.h"
#include "Interfaz/Objeto_Motor.h"

#include "Personajes/Character.h"
#include "Datos_Partida.h"
#include "Interfaz/Motor.h"
#include "Game.h"
#include "Respawn.h"


#include "Personajes/Player.h"


Zona_Coliseo::Zona_Coliseo(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo, uint16_t num_enemigos, uint16_t rondas) : Zona(_i_x, _i_y, _i_z, long_x, long_y, i_equipo){
    _num_enemigos = num_enemigos;
    _rondas = rondas;
}

Zona_Coliseo::~Zona_Coliseo() {

}


/*Metodo para actualizar los valores de la zona*/

void Zona_Coliseo::actualizar_zona(){
    if(esta_jugador_en_zona()){
        if(!_coliseo_iniciado){
            iniciar_coliseo();
        }
        else{
            update_coliseo();
        }
    }
}


void Zona_Coliseo::iniciar_coliseo(){
    
    Respawn* _respawn = Respawn::posiciones_instancia();
    _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, true);

    _coliseo_iniciado=true;
}


void Zona_Coliseo::update_coliseo(){
    if(get_num_npc_en_zona()==0 && _rondas>0){
        Respawn* _respawn = Respawn::posiciones_instancia();
        _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, true);
        _rondas--;
    }

}