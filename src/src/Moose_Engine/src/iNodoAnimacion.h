#ifndef SRC_INODOANIMACION_H_
#define SRC_INODOANIMACION_H_
#include "../../Utilidades/Vector.h"
#include "iNodoModelado.h"

class iNodoAnimacion : public iNodoModelado{
    public:
        iNodoAnimacion(bool bucle, const char* ruta, uint8_t _num_ruta);
        iNodoAnimacion(bool bucle, const char* ruta, float x, float y, float z, uint8_t _num_ruta);
        void cambiar_modelado(const char * _i_ruta, uint8_t _num_ruta) override;
        ~iNodoAnimacion();
    private:
        bool _i_bucle;
        uint8_t _ruta_actual;
};

#endif