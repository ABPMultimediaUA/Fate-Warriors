#ifndef SRC_INODOANIMACION_H_
#define SRC_INODOANIMACION_H_
#include "../../Utilidades/Vector.h"
#include "iNodoModelado.h"

class iNodoAnimacion : public iNodoModelado{
    public:
        iNodoAnimacion(bool bucle, const char* ruta);
        iNodoAnimacion(bool bucle, const char* ruta, float x, float y, float z);
        void cambiar_modelado(const char * _i_ruta) override;
        ~iNodoAnimacion();
        Vector3 getBB() override;
    private:
        bool _i_bucle;
};

#endif