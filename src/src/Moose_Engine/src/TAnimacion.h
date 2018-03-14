#ifndef SRC_TANIMACION_H_
#define SRC_TANIMACION_H_
#include "TEntidad.h"
#include <vector>
class TRecursoModelado;
class Shader;
class TAnimacion : public TEntidad{
    public:
        TAnimacion(const char* path);
        ~TAnimacion();
        void beginDraw(Shader* _i_shader) override;
        void draw(Shader* _i_shader);
        void endDraw();
        
    private:
        std::vector<TRecursoModelado*> _modelos;
        std::string _path;     

        void leerAnimacion(std::string &path);

};

#endif /* SRC_TANIMACION_H_ */