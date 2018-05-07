#ifndef ZONA_H_
#define ZONA_H_

#include "../Objeto.h"

#include <vector>

class Character;
class Time;
class Interruptor;
class Puerta_Pincho;
class Interfaz_sonido;

class Zona{
public:
	Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y);
    virtual ~Zona();
    
    virtual void actualizar_zona();

    bool esta_jugador_en_zona();

    inline btRigidBody * getRigidBody(){return _rb; }

    inline float getX(){                return _pos_x; }
    inline float getY(){                return _pos_y; }
    inline float getZ(){                return _pos_y; }


	inline int get_npcs_persiguiendome(){          return _npcs_persiguiendome; }
	inline void incrementar_npcs_persiguiendome(){ _npcs_persiguiendome++; }
	inline void decrementar_npcs_persiguiendome(){ _npcs_persiguiendome--; }
	inline void reiniciar_npcs_persiguiendome(){   _npcs_persiguiendome = 0; }


    std::vector<Interruptor*> get_interruptores_asociados();
    void set_interruptor_asociado(Interruptor* _i_interruptor);
    uint8_t get_num_npc_en_zona();

    void set_puerta_pincho_asociada(Puerta_Pincho* _i_puerta_pincho);
    void eliminar_npc_de_zona(Character* _i_npc);

protected:

    float distancia_player_a_zona();
    void activar_todas_las_puerta_pincho();
    void desactivar_todas_las_puerta_pincho();
    void restaurar_vida_enemigos_zona();

    btRigidBody *_rb;

    float _pos_x;
    float _pos_y; // Es la Z realmente

    Time* _reloj;

    float _long_x;
    float _long_y;

    std::vector<Character*> _npc_en_la_zona;
    int _npcs_persiguiendome;
    std::vector<Interruptor*> _interruptores_asociados;
    std::vector<Puerta_Pincho*> _puerta_pincho_asociados;

    Interfaz_sonido* _sonido;
};

#endif /* ZONA_H_ */