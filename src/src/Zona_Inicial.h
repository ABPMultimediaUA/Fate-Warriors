#ifndef ZONA_INICIAL_H_
#define ZONA_INICIAL_H_

#include "Objeto.h"
#include "Personajes/Enum_Tipo_Ataque.h"
#include "Zona.h"

#include <vector>

class Character;
class Time;
class Interruptor;

class Zona_Inicial : public Zona{
public:
	Zona_Inicial(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    ~Zona_Inicial();
    void actualizar_zona();
    std::vector <Character*>get_characters();
    void iniciar_tiempo_conquista();
    void cambiar_bando();

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

};

#endif /* ZONA_INICIAL_H_ */