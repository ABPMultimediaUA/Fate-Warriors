#ifndef SRC_INODOMODELADO_H_
#define SRC_INODOMODELADO_H_

#include "iNodo.h"

class iNodoModelado : public iNodo{
    public:
        iNodoModelado(const char* ruta);
        iNodoModelado(const char* ruta, float x, float y, float z);
        ~iNodoModelado();
    private:
};

#endif