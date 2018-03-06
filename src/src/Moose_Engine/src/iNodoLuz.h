#ifndef SRC_INODOLUZ_H_
#define SRC_INODOLUZ_H_

#include "iNodo.h"

class iNodoLuz : public iNodo{
    public:
        iNodoLuz(bool activa, float intensidad);
        ~iNodoLuz();
    private:
};

#endif