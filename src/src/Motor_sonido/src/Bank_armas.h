#ifndef SRC_BANK_ARMAS_H_
#define SRC_BANK_ARMAS_H_
#include "Evento_sonido.h"
class Bank_armas: public Evento_sonido{
    public:
        Bank_armas(std::string _i_ruta);
        ~Bank_armas();
};
#endif 