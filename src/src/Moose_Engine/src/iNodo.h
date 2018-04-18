#ifndef SRC_INODO_H_
#define SRC_INODO_H_
#include "../../Utilidades/Vector.h"

class TNodo;

class iNodo{
    public:
        iNodo();
        ~iNodo();
        void mover  (float x, float y, float z);
        void mover  (Vector3 posicion);
        void rotar  (float x, float y, float z, float w); 
        void rotacionDirecta(float x, float y, float z, float w);
        void escalar(float x, float y, float z);
        Vector3 getPosition();
        void borrarNodo();

    protected:
        TNodo* _nodo_motor; //nodo interno del ME
};

#endif