#ifndef SRC_INODOLUZ_H_
#define SRC_INODOLUZ_H_

#include "iNodo.h"

class iNodoLuz : public iNodo{
    public:
        iNodoLuz(bool activa, float intensidad);
        iNodoLuz(bool activa, float intensidad, float x, float y, float z);
        
        ~iNodoLuz();
    private:
};

#endif