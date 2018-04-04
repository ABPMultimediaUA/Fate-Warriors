#ifndef SRC_TANIMACION_H_
#define SRC_TANIMACION_H_
#include "TEntidad.h"
class Shader;
class TRecursoAnimacion;
class TAnimacion : public TEntidad{
    public:
        TAnimacion(const char* path);
        ~TAnimacion();
        void beginDraw(Shader* _i_shader) override;
        void draw(Shader* _i_shader);
        void endDraw();
        
    private:
        const char* _path;     
        TRecursoAnimacion* _animacion;
        void leerAnimacion(const char* path);

};

#endif /* SRC_TANIMACION_H_ */