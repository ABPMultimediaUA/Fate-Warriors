#ifndef SRC_EVENTO_CONSUMIBLES_H_
#define SRC_EVENTO_CONSUMIBLES_H_
#include "Evento_sonido.h"
class Evento_consumibles: public Evento_sonido{
    public:
        Evento_consumibles(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_consumibles();
        void start() override;
};
#endif 