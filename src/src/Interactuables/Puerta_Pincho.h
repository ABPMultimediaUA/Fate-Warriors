#ifndef HEADERS_PUERTA_PINCHO_H_
#define HEADERS_PUERTA_PINCHO_H_

#include "../Objeto.h"

class Pinchos;
class Time;
class Zona;

#include <cstdint>

class Puerta_Pincho  : public Objeto {
public:
	Puerta_Pincho(short id, float _i_x, float _i_y, float _i_z, bool activada, float _i_rotacion, uint8_t _i_pasillo_asociado);
	~Puerta_Pincho();

    void activar();
    void desactivar();
    void cambiar_estado();

    inline bool get_activado() { return _activado;}

private:
    bool _activado;

    uint8_t _pasillo_asociado;
    
    Objeto_Motor* _basecita;
};

#endif /* HEADERS_PUERTA_PINCHO_H_ */
