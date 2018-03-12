#ifndef INTERFAZ_ME_H
#define INTERFAZ_ME_H


#include <cstdint>

#include "iNodoModelado.h"
#include "iNodoCamara.h"
#include "iNodoLuz.h"
#include <vector>
#include "EnumTiposBoundingBox.h"
#include <btBulletCollisionCommon.h>
#include "../Utilidades/Vector.h"

class TMooseEngine;

class Interfaz_ME{

    public:    
        ~Interfaz_ME();
        static Interfaz_ME* get_instancia(uint16_t width, uint16_t height);

        iNodoModelado* crearModelado(const char* ruta);
        iNodoModelado* crearModelado(const char* ruta, float x, float y, float z);
        iNodoCamara* crearCamara(bool activa); 
        iNodoCamara* crearCamara(bool activa, float x, float y, float z);
        iNodoLuz* crearLuz(bool activa, float intensidad);
        iNodoLuz* crearLuz(bool activa, float intensidad, float x, float y, float z);

        void render();
        bool ventana_abierta();
        TMooseEngine* getEngine();

    private:
        static Interfaz_ME* _instancia;
        TMooseEngine* motor;
        Interfaz_ME(uint16_t width, uint16_t height);
        void configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync);
        //void configuracion_bullet();
        std::vector<iNodo*> lista_i_nodo;        
};

#endif