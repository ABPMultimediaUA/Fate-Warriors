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
class Mapeado;


class TMooseEngine{

    public:
        TMooseEngine();
        ~TMooseEngine();

        TNodo*      crearNodo(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoCamara(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoLuz(TNodo *padre, TEntidad *ent);
        TTransform* crearTransform();
        TCamara*    crearCamara();
        TLuz*       crearLuz();
        TMalla*     crearMalla(char* fichero);
        
        inline TNodo* nodoRaiz(){
            return _escena;
        }
        void draw();

    private:
        Mapeado *mapping_camaras;
        Mapeado *mapping_luces;
        TNodo* _escena;
        TGestorRecursos* _gestorRecursos;
        uint16_t _contadorIDEntidad;
        uint8_t n_camaras,n_c_actual;
        uint8_t n_luces,n_l_actual;
        //atributos para camaras, luces y demás
};


#endif /* SRC_TMOOSEENGINE_H_ */