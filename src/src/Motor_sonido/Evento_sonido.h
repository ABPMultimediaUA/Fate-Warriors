#ifndef SRC_EVENTO_SONIDO_H_
#define SRC_EVENTO_SONIDO_H_

#include "FMOD/fmod_studio.hpp"
#include <string>

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)
class Evento_sonido{
    public:
        Evento_sonido(std::string _i_ruta, FMOD::Studio::System *sys);
        virtual ~Evento_sonido();
        virtual void start();
        void set_position(float _i_x, float _i_y, float _i_z);
        void poner_cant_eventos(unsigned short _i_cant);
    protected:
        FMOD::Studio::EventInstance* _instancia;
        FMOD::Studio::EventDescription* _evento;
        void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
};
#endif 
