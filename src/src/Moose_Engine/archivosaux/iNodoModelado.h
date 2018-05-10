#ifndef SRC_INODOMODELADO_H_
#define SRC_INODOMODELADO_H_
#include "../../Utilidades/Vector.h"
#include "iNodo.h"

class iNodoModelado : public iNodo{
    public:
        iNodoModelado();
        iNodoModelado(const char* ruta);
        iNodoModelado(const char* ruta, float x, float y, float z);
        virtual void cambiar_modelado(const char * _i_ruta);
        void remove();
        virtual Vector3 getBB();
        virtual ~iNodoModelado();
    private:
};

#endif