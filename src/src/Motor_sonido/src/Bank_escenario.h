#ifndef SRC_BANK_ESCENARIO_H_
#define SRC_BANK_ESCENARIO_H_
#include "Evento_sonido.h"
class Bank_escenario: public Evento_sonido{
    public:
        Bank_escenario(std::string _i_ruta);
        ~Bank_escenario();
};
#endif 