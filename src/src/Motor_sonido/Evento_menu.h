#ifndef SRC_EVENTO_MENU_H_
#define SRC_EVENTO_MENU_H_
#include "Evento_sonido.h"
class Evento_menu: public Evento_sonido{
    public:
        Evento_menu(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys);
        ~Evento_menu();
        void start() override;
};
#endif 