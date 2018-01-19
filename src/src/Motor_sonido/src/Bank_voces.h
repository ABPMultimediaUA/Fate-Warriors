#ifndef SRC_BANK_VOCES_H_
#define SRC_BANK_VOCES_H_
#include "Evento_sonido.h"
class Bank_voces: public Evento_sonido{
    public:
        Bank_voces(std::string _i_ruta);
        ~Bank_voces();
};
#endif 