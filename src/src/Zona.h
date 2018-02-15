#ifndef ZONA_H_
#define ZONA_H_

#include "Objeto.h"
#include "Personajes/Enum_Tipo_Ataque.h"
#include <vector>

class Character;
class Time;

class Zona{
public:
	Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    ~Zona();
    void actualizar_zona();
    std::vector <Character*>get_characters();
    void iniciar_tiempo_conquista();
    void cambiar_bando();

    inline btRigidBody * getRigidBody(){
        return _rb;
    }

    inline Enum_Equipo get_equipo(){
        return _equipo;
    }

    inline float getX(){
        return _pos_x;
    }
    inline float getY(){
        return _pos_y;
    }
    inline float getZ(){
        return _pos_y;
    }
    inline bool siendo_capturada(){
        return _conquistando;
    }

    int _num_characters_equipo_A;
    int _num_characters_equipo_B;

private:
    btRigidBody *_rb;
    Enum_Equipo _equipo;

    int _pos_x;
    int _pos_y; // Es la Z realmente

    Time* _reloj;
    std::vector <Character*> personajes_de_la_zona;
    bool _conquistando;
    double _tiempo_inicio_conquista;
};

#endif /* ZONA_H_ */