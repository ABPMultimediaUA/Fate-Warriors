#ifndef HEADERS_PUERTA_PINCHO_H_
#define HEADERS_PUERTA_PINCHO_H_


#include <cstdint>

#include "Objeto.h"

class Pinchos;
class Time;
class Zona;

class Puerta_Pincho  : public Objeto {
public:

	Puerta_Pincho(short id, float _i_x, float _i_y, float _i_z ,float _i_rotacion, Zona* _i_asociada_1, Zona* _i_asociada_2, uint8_t _i_pasillo_asociado);
	~Puerta_Pincho();
    void update();
    void activar();
    void desactivar();
    bool comprobar_si_finalizo_el_tiempo();
    bool get_activado();
    void comprobar_a_quien_danya();
    bool puede_quitar_vida();
    void render(){}
    inline Zona* get_zona_1(){
        return _zona_asociada1;
    }
    inline Zona* get_zona_2(){
        return _zona_asociada2;
    }
    bool ha_pasado_tiempo_suficiente();


private:

    double _tiempo_hasta_posible_proxima_activacion;
    uint8_t _pasillo_asociado;
    double _siguiente_tiempo_hace_danyo;
    Zona* _zona_asociada1;
    Zona* _zona_asociada2;
    Time* _reloj;
    bool _activado;
    double _tiempo_restante;
};

#endif /* HEADERS_PUERTA_PINCHO_H_ */
