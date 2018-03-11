
#include "Respawn.h"
#include "Nivel/Nivel.h"
#include "Zona.h"
#include "Zonas_Manager.h"
#include "Datos_Partida.h"
#include "Personajes/Character.h"
#include "Tiempo/Time.h"
#include "Game.h"

Respawn* Respawn::instancia = 0;

Respawn* Respawn::posiciones_instancia(){
	if(instancia == 0){
		instancia= new Respawn();
	}

	return instancia;
}

Respawn::Respawn(){
     Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);
}


Respawn::~Respawn(){
    eliminar_datos();
}


Vector2 Respawn::generar_posicion_al_azar_xz(){    
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}


Vector2 Respawn::generar_posicion_del_bando(Enum_Equipo _i_bando){
	
    Game* puntero 		= Game::game_instancia();
	Datos_Partida * datitos	= puntero->game_get_datos();

	std::vector<Zona*> zona_bando;
    
    if(_i_bando == Enum_Equipo_A){
        zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_a_no_siendo_conquistadas();
        if(zona_bando.size()==0){
            zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_a();
        }
    }
    else if (_i_bando == Enum_Equipo_B){
        zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_b_no_siendo_conquistadas();
        if(zona_bando.size()==0){
            zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_b();
        }
    }

    if(zona_bando.size()>0){
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % zona_bando.size();

    int8_t zona_al_azar_exactamente_x = (rand() % 50) - 25;
    int8_t zona_al_azar_exactamente_z = (rand() % 50) - 25;


    return Vector2(zona_bando[posicion_al_azar]->getX() + zona_al_azar_exactamente_x, zona_bando[posicion_al_azar]->getZ() + zona_al_azar_exactamente_z);
    }
    else{
      return Vector2(0, 0);
    }
}

void Respawn::comprobar_si_renace_y_renacer_personaje(Character* _i_personaje){
    if(Time::Instance()->get_current()>_character_a_reaparecer[_i_personaje]){
        Vector2 pos = generar_posicion_del_bando(_i_personaje->get_equipo());
        _i_personaje->revivir(pos);

        eliminar_character_a_reaparecer(_i_personaje);
    }
}

void Respawn::anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo){
    _character_a_reaparecer[_i_character] = _i_tiempo;
}
void Respawn::eliminar_character_a_reaparecer(Character* _i_character){
    _character_a_reaparecer.erase (_i_character);
}

void Respawn::eliminar_datos(){
    Respawn::instancia = 0;
    vaciar_map();
    eliminar_puntos();
}

void Respawn::vaciar_map(){
    _character_a_reaparecer.clear();
}

void Respawn::eliminar_puntos(){
  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;

}


