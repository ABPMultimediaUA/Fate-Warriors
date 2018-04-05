#ifndef ZONA_H_
#define ZONA_H_

#include "Objeto.h"
#include "Personajes/Enum_Tipo_Ataque.h"
#include <vector>

class Character;
class Time;
class Interruptor;
class Puerta_Pincho;

class Zona{
public:
	Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    virtual ~Zona();
    virtual void actualizar_zona();
    std::vector <Character*>get_characters();
    void iniciar_tiempo_conquista();
    void cambiar_bando();


    bool esta_jugador_en_zona();

    void set_tiempo_restante_para_conquistar();
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


	inline int get_npcs_persiguiendome(){
		return _npcs_persiguiendome;
	}
	inline void incrementar_npcs_persiguiendome(){
		_npcs_persiguiendome++;
	}
	inline void decrementar_npcs_persiguiendome(){
		_npcs_persiguiendome--;
	}
	inline void reiniciar_npcs_persiguiendome(){
		_npcs_persiguiendome = 0;
	}

    int _num_characters_equipo_A;
    int _num_characters_equipo_B;

    bool hay_personajes_conquistando_esta_zona();
    bool get_conquistando();
   
    std::vector<Interruptor*> get_interruptores_asociados();
    void set_interruptor_asociado(Interruptor* _i_interruptor);
    uint8_t get_num_npc_en_zona();

    void activar_todos_los_interruptores();
    void desactivar_todos_los_interruptores();

    void set_puerta_pincho_asociada(Puerta_Pincho* _i_puerta_pincho);

protected:

    float distancia_player_a_zona();
    void activar_todas_las_puerta_pincho();
    void desactivar_todas_las_puerta_pincho();

    btRigidBody *_rb;
    Enum_Equipo _equipo;

    float _pos_x;
    float _pos_y; // Es la Z realmente

    Time* _reloj;
    std::vector <Character*> personajes_de_la_zona;
    bool _conquistando;
    double _tiempo_inicio_conquista;
    double _tiempo_restante_conquista;
    float _long_x;
    float _long_y;

    int _npcs_persiguiendome;
    std::vector<Interruptor*> _interruptores_asociados;
    std::vector<Puerta_Pincho*> _puerta_pincho_asociados;
};

#endif /* ZONA_H_ */