#ifndef SRC_EVENTO_PERSONAJE_H_
#define SRC_EVENTO_PERSONAJE_H_
#include "Evento_sonido.h"
class Evento_personaje: public Evento_sonido{
    public:
        Evento_personaje(std::string _i_ruta);
        ~Evento_personaje();
};
#endif 