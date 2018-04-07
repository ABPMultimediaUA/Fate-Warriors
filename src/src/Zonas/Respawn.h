#ifndef POSICIONES_RESPAWN_H_
#define POSICIONES_RESPAWN_H_

#include "../Utilidades/Vector.h" 
#include "../Personajes/Enum_Tipo_Ataque.h"

#include <cstdint>
#include <map>
#include <vector>

class Character;
class Nivel;

class Respawn {

public:
	static Respawn* posiciones_instancia();
	~Respawn();

    void crear_zonas_respawn(Nivel* _i_nivel);
    void eliminar_zonas_respawn();
	
    void anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo);
    void eliminar_character_a_reaparecer(Character* _i_character);
    void comprobar_si_renace_y_renacer_personaje(Character* _i_personaje);

    void eliminar_datos();
    void eliminar_puntos();
    void vaciar_map();


    Vector2 generar_posicion_al_azar_xz();
    Vector2 generar_posicion_del_bando(Enum_Equipo _i_bando);
    std::map<Character*, double> jugadores_a_revivir();
    void renacer_personaje_en_posicion(Character* _i_personaje, Vector2 posicion);
    std::vector<Character*> revivir_enemigos_en_zona(uint8_t num_npc, float _pos_x, float _pos_z, bool inmediatamente);


private:

    std::map<Character*, double> _character_a_reaparecer;
    std::vector<Character*> _personajes_muertos;
    Respawn();
	static Respawn* instancia;
    // Zonas del mapa (puntos de los nodos)
   	uint16_t cantidad_de_posiciones;
    float ** posiciones;

};

#endif /* POSICIONES_RESPAWN_H_ */
