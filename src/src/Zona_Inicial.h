#ifndef ZONA_INICIAL_H_
#define ZONA_INICIAL_H_

#include "Objeto.h"
#include "Personajes/Enum_Tipo_Ataque.h"
#include "Zona.h"

#include <vector>

class Character;
class Time;
class Interruptor;
class Player;

class Zona_Inicial : public Zona{
public:
	Zona_Inicial(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    Zona_Inicial(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo, float _i_x_inicial, float _i_y_inicial);
    ~Zona_Inicial();
    void actualizar_zona();
    Vector2 get_posicion_inicial();  

private:
    float _x_inicial;
    float _y_inicial;
};

#endif /* ZONA_INICIAL_H_ */