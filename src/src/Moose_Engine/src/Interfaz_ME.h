#ifndef INTERFAZ_ME_H
#define INTERFAZ_ME_H


#include <cstdint>

class TMooseEngine;

class Interfaz_ME{
    public:
        
        ~Interfaz_ME();
        static Interfaz_ME* get_instancia(uint16_t width, uint16_t height);
        void crearModelado(char* ruta, float x, float y, float z);

        uint16_t crearCamara();
        uint16_t crearLuz();

        void render();
        bool ventana_abierta();

    private:
        static Interfaz_ME* _instancia;
        TMooseEngine* motor;
        Interfaz_ME(uint16_t width, uint16_t height);
        void configuracion_motor(uint16_t width, uint16_t height, bool fullscreen, bool v_sync);
        
};

#endif