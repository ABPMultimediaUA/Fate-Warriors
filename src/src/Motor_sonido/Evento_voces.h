#ifndef SRC_EVENTO_VOCES_H_
#define SRC_EVENTO_VOCES_H_
#include "Evento_sonido.h"
class Evento_voces: public Evento_sonido{
    public:
        Evento_voces(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys);
        ~Evento_voces();
};
#endif 