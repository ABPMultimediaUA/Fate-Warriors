#ifndef SRC_EVENTO_AMBIENTE_H_
#define SRC_EVENTO_AMBIENTE_H_
#include "Evento_sonido.h"
class Evento_ambiente: public Evento_sonido{
    public:
        Evento_ambiente(std::string _i_ruta);
        ~Evento_ambiente();
};
#endif 