#include "Zona_Final.h"

#include "Respawn.h"
#include "../Personajes/Character.h"
#include "../Motor_sonido/Interfaz_sonido.h"
#include "../Game.h"


Zona_Final::Zona_Final(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos, int rondas, uint8_t crec_enem, uint8_t music_ini) : Zona(_i_x, _i_y, _i_z, long_x, long_y){
    _num_enemigos = num_enemigos;
    _rondas = rondas;
    _zona_fina_iniciado = false;
    
    _crecimiento_enemigos = crec_enem;

    _musica_inicio = music_ini;
}

Zona_Final::~Zona_Final() {

}


/*Metodo para actualizar los valores de la zona*/

void Zona_Final::actualizar_zona(){
    if(esta_jugador_en_zona()){
        if(!_zona_fina_iniciado){
            iniciar_zona_final();
        }
        else{
            update_zona_fina();
        }
    }
}

void Zona_Final::iniciar_zona_final(){
    Respawn* _respawn = Respawn::posiciones_instancia();
    _npc_en_la_zona = _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, _long_x, _long_y, this);
    activar_todas_las_puerta_pincho();
    _zona_fina_iniciado=true;
    _rondas--;

    _sonido->play_music(_musica_inicio);
}


void Zona_Final::update_zona_fina(){
    if(get_num_npc_en_zona()==0){
        if( _rondas>0){
            _num_enemigos += _crecimiento_enemigos;

            Respawn* _respawn = Respawn::posiciones_instancia();
            _npc_en_la_zona = _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, _long_x, _long_y, this);
            _rondas--;
        }

        else if(_rondas==0){
            desactivar_todas_las_puerta_pincho();
            _rondas--; //Valdra -1 asi no se podra meter en ninguno de los dos metodos
            Game::game_instancia()->cambio_a_update_win();
        }
    
    }
}