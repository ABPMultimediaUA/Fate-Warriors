#ifndef POSICIONES_RESPAWN_H_
#define POSICIONES_RESPAWN_H_

#include "../Utilidades/Vector.h" 
#include "../Personajes/Enum_Tipo_Ataque.h"

#include <cstdint>
#include <map>
#include <vector>

class Character;
class Nivel;
class Zona;

class Respawn {

public:
	static Respawn* posiciones_instancia();
	~Respawn();

    
    void leer_posiciones_de_respawn_del_nivel();
    void eliminar_zonas_respawn();
	
    void anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo);
    void eliminar_character_a_reaparecer(Character* _i_character);

    void eliminar_datos();
    void eliminar_puntos();
    void vaciar_vector_personajes_muertos();

    Vector2 generar_posicion_al_azar_xz();
    std::vector<Character*> jugadores_a_revivir();
    void renacer_personaje_en_posicion(Character* _i_personaje, Vector2 posicion);
    std::vector<Character*> revivir_enemigos_en_zona(uint8_t num_npc, float _pos_x, float _pos_z, Zona* _zona);


private:

    std::vector<Character*> _personajes_muertos;
    Respawn();
	static Respawn* instancia;
    // Zonas del mapa (puntos de los nodos)
   	uint16_t cantidad_de_posiciones;
    float ** posiciones;

};

#endif /* POSICIONES_RESPAWN_H_ */
