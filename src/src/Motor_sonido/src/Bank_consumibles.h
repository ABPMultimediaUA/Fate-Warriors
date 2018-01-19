#ifndef SRC_BANK_CONSUMIBLES_H_
#define SRC_BANK_CONSUMIBLES_H_
#include "Evento_sonido.h"
class Bank_consumibles: public Evento_sonido{
    public:
        Bank_consumibles(std::string _i_ruta);
        ~Bank_consumibles();
};
#endif 