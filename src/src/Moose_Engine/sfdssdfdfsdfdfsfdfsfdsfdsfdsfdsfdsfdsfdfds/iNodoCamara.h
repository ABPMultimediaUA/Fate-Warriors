#ifndef SRC_INODOCAMARA_H_
#define SRC_INODOCAMARA_H_

#include "iNodo.h"

struct Vector3;

class iNodoCamara : public iNodo{
    public:
        iNodoCamara(bool activa);
        iNodoCamara(bool activa, float x, float y, float z);
        ~iNodoCamara() = default;
        //metodos para el plan de emergencia
        void mover(float x, float y, float z);
        void mover  (Vector3 posicion);
        void LookAt(Vector3 position, Vector3 target);
        void setPosition(Vector3 position);
        void setTarget(Vector3 target);
        
    private:

};

#endif