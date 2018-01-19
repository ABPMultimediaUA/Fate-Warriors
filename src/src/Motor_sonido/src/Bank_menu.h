#ifndef SRC_BANK_MENU_H_
#define SRC_BANK_MENU_H_
#include "Evento_sonido.h"
class Bank_menu: public Evento_sonido{
    public:
        Bank_menu(std::string _i_ruta);
        ~Bank_menu();
};
#endif 