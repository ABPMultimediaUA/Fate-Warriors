#ifndef SRC_INODOCAMARA_H_
#define SRC_INODOCAMARA_H_

#include "iNodo.h"

class iNodoCamara : public iNodo{
    public:
        iNodoCamara(bool activa);
        iNodoCamara(bool activa, float x, float y, float z);
        ~iNodoCamara() = default;
    private:

};

#endif