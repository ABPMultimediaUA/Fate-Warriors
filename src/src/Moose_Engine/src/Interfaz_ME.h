#ifndef INTERFAZ_ME_H
#define INTERFAZ_ME_H


#include <cstdint>

#include "iNodoModelado.h"
#include "iNodoCamara.h"

class TMooseEngine;

class Interfaz_ME{

    public:    
        ~Interfaz_ME();
        static Interfaz_ME* get_instancia(uint16_t width, uint16_t height);
        iNodoModelado* crearModelado(const char* ruta, float x, float y, float z);

        iNodoCamara* crearCamara(bool activa, float x, float y, float z);
        uint16_t crearLuz();

        void render();
        bool ventana_abierta();
        TMooseEngine* getEngine();

    private:
        static Interfaz_ME* _instancia;
        TMooseEngine* motor;
        Interfaz_ME(uint16_t width, uint16_t height);
        void configuracion_motor(uint16_t width, uint16_t height, bool fullscreen, bool v_sync);
        
};

#endif