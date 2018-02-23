#ifndef SRC_TMALLA_H_
#define SRC_TMALLA_H_
#include "TEntidad.h"
#include <vector>
class TRecursoMalla;
class TFichero;

class TMalla : public TEntidad{
    public:
        TMalla();
        ~TMalla();
        void cargarMalla(TFichero _i_fichero);
        void draw();
        void beginDraw();
        void endDraw();
        
    private:
        std::vector<TRecursoMalla*> mallas;
        glm::mat4 _t_matriz;
        
};

#endif /* SRC_TMALLA_H_ */