#ifndef SRC_TMODELADO_H_
#define SRC_TMODELADO_H_
#include "TEntidad.h"
class TRecursoMalla;
class TRecursoModelado;
class TFichero;

class Shader;

class TModelado : public TEntidad{
    public:
        TModelado(const char* path);
        ~TModelado();
        
        void draw(Shader* _i_shader);
        void beginDraw(Shader* _i_shader) override;
        void endDraw();
        glm::vec3 get_BB();
        
    private:
        
        TRecursoModelado* _modelado;
        std::string _path;

        void leerModelado(const char* path);

};

#endif /* SRC_TMODELADO_H_ */