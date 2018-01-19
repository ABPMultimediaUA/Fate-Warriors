#ifndef SRC_BANK_PERSONAJE_H_
#define SRC_BANK_PERSONAJE_H_
#include "Evento_sonido.h"
class Bank_personaje: public Evento_sonido{
    public:
        Bank_personaje(std::string _i_ruta);
        ~Bank_personaje();
};
#endif 