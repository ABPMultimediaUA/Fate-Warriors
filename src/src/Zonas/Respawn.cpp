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
     Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);
}

////////////////////// ELIMINAR DATOS

Respawn::~Respawn(){
    eliminar_datos();
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

// GENERAR POSICIONES EN CUALQUIER ZONA DEL MAPA


Vector2 Respawn::generar_posicion_al_azar_xz(){    
    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}

// GENERAR POSICION DEL BANDO

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

// REVIVIR PERSONAJES EN POSICION DEL BANDO

void Respawn::comprobar_si_renace_y_renacer_personaje(Character* _i_personaje){
    if(Time::Instance()->get_current()>_character_a_reaparecer[_i_personaje]){
        Vector2 pos = generar_posicion_del_bando(_i_personaje->get_equipo());
        renacer_personaje_en_posicion(_i_personaje, pos);
    }
}

// REVIVIR DADA UNA POSICION

void Respawn::renacer_personaje_en_posicion(Character* _i_personaje, Vector2 posicion){
        _i_personaje->revivir(posicion);
        eliminar_character_a_reaparecer(_i_personaje);
}

// ANYADIR MUERTO AL MAPA DE LOS MUERTOS

void Respawn::anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo){
    _character_a_reaparecer[_i_character] = _i_tiempo;
}

// REVIVIR X ENEMIGOS DEVUELVE LA CANTIDAD DE ENEMIGOS QUE HA PODIDO REVIVIR
std::vector <Character*> Respawn::revivir_enemigos_en_zona(uint8_t num_npc, float _pos_x, float _pos_y, bool _inmediatamente, Zona* _zona){

   int8_t zona_al_azar_exactamente_x;
   int8_t zona_al_azar_exactamente_z;
   uint8_t cont = 0;
    
   uint8_t he_podido_revivir = 0;
   std::vector <Character*> _enemigos_que_creo;
   
    for (std::map<Character*, double>::iterator it=_character_a_reaparecer.begin(); cont<num_npc && it!=_character_a_reaparecer.end(); ++it){
        zona_al_azar_exactamente_x = (rand() % 50) - 25;
        zona_al_azar_exactamente_z = (rand() % 50) - 25;

        if(_inmediatamente){
            renacer_personaje_en_posicion(it->first, Vector2(_pos_x+zona_al_azar_exactamente_x, _pos_y+zona_al_azar_exactamente_z));
            _enemigos_que_creo.push_back(it->first);
            (it->first)->set_zona_en_la_que_se_encuentra(_zona);
            it=_character_a_reaparecer.begin();
            cont++;
        }
        else if(Time::Instance()->get_current()>it->second){
            renacer_personaje_en_posicion(it->first, Vector2(_pos_x+zona_al_azar_exactamente_x, _pos_y+zona_al_azar_exactamente_z));
            it=_character_a_reaparecer.begin();
        }
        he_podido_revivir++;
        
    }

    return _enemigos_que_creo;
}

// GET ENEMIGOS MUERTOS

std::map<Character*, double> Respawn::jugadores_a_revivir(){
    return _character_a_reaparecer;
}
