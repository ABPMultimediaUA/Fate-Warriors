
#include "Posiciones_Respawn.h"
#include "Nivel/Nivel.h"

Posiciones_Respawn* Posiciones_Respawn::instancia = 0;

Posiciones_Respawn* Posiciones_Respawn::nivel_instancia(){
	if(instancia == 0){
		instancia= new Posiciones_Respawn();
	}

	return instancia;
}

Posiciones_Respawn::Posiciones_Respawn(){
     Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);
}


Posiciones_Respawn::~Posiciones_Respawn(){
  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;
}


Vector2 Posiciones_Respawn::generar_posicion_al_azar_xz(){    
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}


Vector2 Posiciones_Respawn::generar_posicion_del_bando(Enum_Equipo _i_bando){
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}