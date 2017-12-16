#include "Llave.h"
#include "Interfaz/Matcher.h"
#include "Utilidades/Modelados.h"

Llave::Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta) : Objeto(_i_id, _i_x, _i_y, _i_z), _id_puerta(_i_id_puerta) {
    _matcher = new Matcher(LLAVE_R, LLAVE_M, _i_x, _i_y, _i_z, 1, false);
}

Llave::~Llave() {
}
