#ifndef POSICIONES_RESPAWN_H_
#define POSICIONES_RESPAWN_H_

#include <cstdint>
#include "Utilidades/Vector.h" 
#include "Personajes/Enum_Tipo_Ataque.h"
#include <vector>


class Nivel;

class Respawn {

public:
	static Respawn* posiciones_instancia();
	~Respawn();

    void crear_zonas_respawn(Nivel* _i_nivel);
    void eliminar_zonas_respawn();
	
  Vector2 generar_posicion_al_azar_xz();
  Vector2 generar_posicion_del_bando(Enum_Equipo _i_bando);

private:

    
    Respawn();
	static Respawn* instancia;
   	uint16_t cantidad_de_posiciones;
    float ** posiciones;

};

#endif /* POSICIONES_RESPAWN_H_ */
