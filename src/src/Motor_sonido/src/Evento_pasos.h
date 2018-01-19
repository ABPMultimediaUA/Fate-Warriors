#ifndef SRC_EVENTO_PASOS_H_
#define SRC_EVENTO_PASOS_H_
#include "Evento_sonido.h"
class Evento_pasos: public Evento_sonido{
    public:
        Evento_pasos(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_pasos();
};
#endif 