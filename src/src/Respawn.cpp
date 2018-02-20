
#include "Respawn.h"
#include "Nivel/Nivel.h"
#include "Zona.h"
#include "Zonas_Manager.h"
#include "Datos_Partida.h"
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
  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;
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
        zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_a();
    }
    else if (_i_bando == Enum_Equipo_B){
        zona_bando = datitos->get_zonas_manager()->get_zonas_equipo_b();
    }

    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % zona_bando.size();

    return Vector2(zona_bando[posicion_al_azar]->getX(), zona_bando[posicion_al_azar]->getZ());
}