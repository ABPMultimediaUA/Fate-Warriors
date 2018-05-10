#include "Respawn.h"

#include "Zona.h"
#include "Zonas_Manager.h"

#include "../Nivel/Nivel.h"
#include "../Datos_Partida.h"
#include "../Personajes/Character.h"
#include "../Tiempo/Time.h"
#include "../Game.h"

Respawn* Respawn::instancia = 0;

Respawn* Respawn::posiciones_instancia(){
	if(instancia == 0){
		instancia= new Respawn();
	}

	return instancia;
}

Respawn::Respawn(){
    leer_posiciones_de_respawn_del_nivel();
}

////////////////////// ELIMINAR DATOS

Respawn::~Respawn(){
    eliminar_datos();
}


void Respawn::leer_posiciones_de_respawn_del_nivel(){
     Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);
}


void Respawn::eliminar_character_a_reaparecer(Character* _i_character){
    _personajes_muertos.erase(_personajes_muertos.begin());
}

void Respawn::eliminar_datos(){
    Respawn::instancia = 0;
    vaciar_vector_personajes_muertos();
    eliminar_puntos();
}

void Respawn::vaciar_vector_personajes_muertos(){
    _personajes_muertos.clear();
}

void Respawn::eliminar_puntos(){
  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;

}

// GENERAR POSICIONES EN CUALQUIER ZONA DEL MAPA

Vector2 Respawn::generar_posicion_al_azar_xz(){    
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}

// REVIVIR DADA UNA POSICION

void Respawn::renacer_personaje_en_posicion(Character* _i_personaje, Vector2 posicion){
    _i_personaje->revivir(posicion);
    eliminar_character_a_reaparecer(_i_personaje);
}

// ANYADIR MUERTO AL MAPA DE LOS MUERTOS COMPRUEBA SI NO HA SIDO ANYADIDO POSTERIORMENTE PARA NO TENER PUNTEROS DUPLICADOS

void Respawn::anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo){
    
    std::vector<Character*>::iterator it;
    it = std::find(_personajes_muertos.begin(), _personajes_muertos.end(), _i_character);
    
    if ( it == _personajes_muertos.end()){
        _personajes_muertos.push_back(_i_character);
    }
}

// REVIVIR X ENEMIGOS DEVUELVE LA CANTIDAD DE ENEMIGOS QUE HA PODIDO REVIVIR
std::vector <Character*> Respawn::revivir_enemigos_en_zona(uint8_t num_npc, float _pos_x, float _pos_y, float _ancho, float _alto, Zona* _zona){

   int8_t zona_al_azar_exactamente_x;
   int8_t zona_al_azar_exactamente_z;
   uint8_t cont = 0;
    
   std::vector <Character*> _enemigos_que_creo;
   uint16_t _cantidad_personajes_muertos = _personajes_muertos.size();


    for(uint8_t cont = 0; cont < num_npc && cont <  _personajes_muertos.size(); cont++){

        asignar_posicion_XZ_al_azar_para_zona(zona_al_azar_exactamente_x, zona_al_azar_exactamente_z, _ancho, _alto);
        _enemigos_que_creo.push_back(_personajes_muertos[0]);
        _personajes_muertos[0]->set_zona_en_la_que_se_encuentra(_zona);
        renacer_personaje_en_posicion(_personajes_muertos[0], Vector2(_pos_x+zona_al_azar_exactamente_x, _pos_y+zona_al_azar_exactamente_z));
        _personajes_muertos[0]->set_pos_azar_en_zona(_pos_x+zona_al_azar_exactamente_x-5, _pos_y+zona_al_azar_exactamente_z-5);
    }
   
    return _enemigos_que_creo;
}

void Respawn::asignar_posicion_XZ_al_azar_para_zona(int8_t& _i_pos_x, int8_t& _i_pos_z, float _ancho, float _alto){
    _i_pos_x = (rand() % (int16_t)_ancho *2) - _ancho;
    _i_pos_z = (rand() % (int16_t)_alto*2) - _alto;
}

// GET ENEMIGOS MUERTOS

std::vector<Character*> Respawn::jugadores_a_revivir(){
    return _personajes_muertos;
}
