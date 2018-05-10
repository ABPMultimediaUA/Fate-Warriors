#ifndef SRC_INODOMODELADOESCENARIO_H_
#define SRC_INODOMODELADOESCENARIO_H_
#include "../../Utilidades/Vector.h"
#include "iNodoModelado.h"

class iNodoModeladoEscenario : public iNodoModelado{
    public:
        iNodoModeladoEscenario() = default;
        iNodoModeladoEscenario(const char* ruta);
        iNodoModeladoEscenario(const char* ruta, float x, float y, float z);
        virtual void cambiar_modelado(const char * _i_ruta);
        Vector3 getBB() override;
        ~iNodoModeladoEscenario() = default;
    private:
};

#endif