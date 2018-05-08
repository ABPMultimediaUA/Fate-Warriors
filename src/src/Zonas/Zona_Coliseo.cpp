#include "Zona_Coliseo.h"

#include "Respawn.h"
#include "../Personajes/Character.h"
#include "../Motor_sonido/Interfaz_sonido.h"

Zona_Coliseo::Zona_Coliseo(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos, int rondas, uint8_t crec_enem, uint8_t music_ini, uint8_t music_fin) : Zona(_i_x, _i_y, _i_z, long_x, long_y){
    _num_enemigos = num_enemigos;
    _rondas = rondas;
    _coliseo_iniciado = false;
    _crecimiento_enemigos = crec_enem;

    _musica_inicio = music_ini;
    _musica_fin = music_fin;
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
    _npc_en_la_zona = _respawn->revivir_enemigos_en_zona(_num_enemigos, _pos_x, _pos_y, _long_x, _long_y, this);
    activar_todas_las_puerta_pincho();
    _coliseo_iniciado=true;
    _rondas--;

    _sonido->play_music(_musica_inicio);
}


void Zona_Coliseo::update_coliseo(){
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
            _sonido->play_music(_musica_fin);
        }
    
    }
}