#ifndef SRC_EVENTO_MENU_H_
#define SRC_EVENTO_MENU_H_
#include "Evento_sonido.h"
class Evento_menu: public Evento_sonido{
    public:
        Evento_menu(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_menu();
};
#endif 