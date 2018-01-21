#ifndef SRC_EVENTO_ESCENARIO_H_
#define SRC_EVENTO_ESCENARIO_H_
#include "Evento_sonido.h"
class Evento_escenario: public Evento_sonido{
    public:
        Evento_escenario(std::string _i_ruta);
        ~Evento_escenario();
};
#endif 