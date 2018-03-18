#ifndef SRC_INODOCAMARA_H_
#define SRC_INODOCAMARA_H_

#include "iNodo.h"

struct Vector3;

class iNodoCamara : public iNodo{
    public:
        iNodoCamara(bool activa);
        iNodoCamara(bool activa, float x, float y, float z);
        void LookAt(Vector3 position, Vector3 target);
        ~iNodoCamara() = default;
    private:

};

#endif