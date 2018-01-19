#ifndef SRC_BANK_AMBIENTE_H_
#define SRC_BANK_AMBIENTE_H_
#include "Evento_sonido.h"
class Bank_ambiente: public Evento_sonido{
    public:
        Bank_ambiente(std::string _i_ruta);
        ~Bank_ambiente();
};
#endif 