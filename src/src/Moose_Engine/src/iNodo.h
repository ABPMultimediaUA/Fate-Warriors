#ifndef SRC_INODO_H_
#define SRC_INODO_H_

class TNodo;

class iNodo{
    public:
        iNodo();
        ~iNodo();
        void mover  (float x, float y, float z);
        void rotar  (float x, float y, float z, float w); 
        void escalar(float x, float y, float z);
    
    protected:
        TNodo* _nodo_motor; //nodo interno del ME
};

#endif