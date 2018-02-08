#ifndef SRC_TMALLA_H_
#define SRC_TMALLA_H_
#include "TEntidad.h"
class TRecursoMalla;
class TFichero;

class TMalla : TEntidad{
    public:
        TMalla();
        ~TMalla();
        void cargarMalla(TFichero _i_fichero);
        void beginDraw();
        void endDraw();
        
    private:
        TRecursoMalla *malla;
};

#endif /* SRC_TMALLA_H_ */