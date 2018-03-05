#ifndef INTERFAZ_ME_H
#define INTERFAZ_ME_H

#include <cstdint>

class TMooseEngine;

class Interfaz_ME{
    public:
        ~Interfaz_ME();
        static Interfaz_ME* get_instancia();
    private:
        static Interfaz_ME* _instancia;
        TMooseEngine* motor;


        Interfaz_ME();
        void configuracion_motor(uint16_t x, uint16_t y, bool fullscreen, bool v_sync);
        void crearModelado(char* ruta, float x, float y, float z);
};

#endif
