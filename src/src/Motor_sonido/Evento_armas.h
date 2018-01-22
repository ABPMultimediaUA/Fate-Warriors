#ifndef SRC_EVENTO_ARMAS_H_
#define SRC_EVENTO_ARMAS_H_
#include "Evento_sonido.h"
class Evento_armas: public Evento_sonido{
    public:
        Evento_armas(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_armas();
};
#endif 