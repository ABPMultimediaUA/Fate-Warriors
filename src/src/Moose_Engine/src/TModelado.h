#ifndef SRC_TMODELADO_H_
#define SRC_TMODELADO_H_
#include "TEntidad.h"
#include <vector>
class TRecursoMalla;
class TFichero;

class Shader;

class TModelado : public TEntidad{
    public:
        TModelado(const char* path);
        ~TModelado();
        void cargarMalla(const char* path);
        void draw(Shader* _i_shader);
        void beginDraw(Shader* _i_shader) override;
        void endDraw();
        
    private:
        std::vector<TRecursoMalla*> _mallas;
        glm::mat4 _t_matriz;
        std::string _path;     

        void leerModelado(std::string &path);

};

#endif /* SRC_TMODELADO_H_ */