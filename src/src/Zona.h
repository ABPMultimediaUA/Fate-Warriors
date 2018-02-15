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

    //void actualizar_characters();
    //Character ** get_characters();
    //int get_num_characters();

private:
    btRigidBody *_rb;
    Enum_Equipo _equipo;

    Time* _reloj;
    std::vector <Character*> personajes_de_la_zona;
    bool _conquistando;
    double _tiempo_inicio_conquista;
    //Character ** _characters;
    //int _num_characters;
};

#endif /* ZONA_H_ */