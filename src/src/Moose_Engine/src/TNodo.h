#ifndef SRC_TNODO_H_
#define SRC_TNODO_H_

#include "TEntidad.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdint>

class TNodo{
    public:
        TNodo(uint16_t entidadID, TNodo* nodo_padre = nullptr);
        ~TNodo();

        TNodo* get_nodo_padre();
        void set_nodo_padre(TNodo* nodo_padre);

        void borrar_nodo();
        bool borrar_hijo(TNodo *hijo);

        void agrega_hijo(TNodo* hijo);
        void agrega_hijo(TEntidad* entidad);

        void draw();

        TEntidad* get_entidad();
        void set_entidad(TEntidad* entidad);
        inline TNodo* get_padre(){
            return _padre; 
        }

        uint16_t get_entidad_id();
        void     set_entidad_id(uint16_t id);

        std::vector<TNodo*>& get_hijos(){return _hijos;}

    private:
        TEntidad *_entidad;
	    TNodo *_padre;
	    std::vector<TNodo*> _hijos;
	    uint16_t _entidadID;
	    bool _visible;
};


#endif /* SRC_TNODO_H_ */