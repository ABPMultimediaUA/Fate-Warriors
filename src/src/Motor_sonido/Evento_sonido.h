#ifndef SRC_EVENTO_SONIDO_H_
#define SRC_EVENTO_SONIDO_H_

#include "FMOD/fmod_studio.hpp"
#include <string>

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)
class Evento_sonido{
    public:
        virtual Evento_sonido(std::string _i_ruta);
        virtual ~Evento_sonido();
    private:
    void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);

};
#endif 