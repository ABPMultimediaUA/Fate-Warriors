#ifndef SRC_EVENTO_AMBIENTE_H_
#define SRC_EVENTO_AMBIENTE_H_
#include "Evento_sonido.h"
class Evento_ambiente: public Evento_sonido{
    public:
        Evento_ambiente(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_ambiente();
        void start() override;
        void stop();
        void pause();
        void quit_pause();
};
#endif 