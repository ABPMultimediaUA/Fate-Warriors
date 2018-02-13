#ifndef SRC_TMOOSEENGINE_H_
#define SRC_TMOOSEENGINE_H_

#include <cstdint>
class TNodo;
class TGestorRecursos;
class TEntidad;
class TTransform;
class TCamara;
class TLuz;
class TMalla;

class TMooseEngine{

    public:
        TMooseEngine();
        ~TMooseEngine();

        TNodo*      crearNodo(TNodo *padre, TEntidad *ent);
        TTransform* crearTransform();
        TCamara*    crearCamara();
        TLuz*       crearLuz();
        TMalla*     crearMalla(char* fichero);
        TNodo*      nodoRaiz();

        void        draw();

    private:
        TNodo* _escena;
        TGestorRecursos* _gestorRecursos;
        uint16_t _contadorIDEntidad;
        //atributos para camaras, luces y demás
};


#endif /* SRC_TMOOSEENGINE_H_ */