#ifndef SRC_TMALLA_H_
#define SRC_TMALLA_H_
#include "TEntidad.h"
#include <vector>
class TRecursoMalla;
class TFichero;
class aiMesh;
class aiScene;
class aiNode;
class Shader;

class TMalla : public TEntidad{
    public:
        TMalla(const char* path);
        ~TMalla();
        void cargarMalla(const char* path);
        void draw(Shader *_i_shader);
        void beginDraw();
        void endDraw();
        
    private:
        std::vector<TRecursoMalla> _mallas;
        glm::mat4 _t_matriz;
        std::string _path;     

        void cargarModelo(std::string &path);
        void cargarNodo(aiNode* nodo, const aiScene* scene);
        TRecursoMalla cargarMalla(aiMesh *mesh, const aiScene *scene);


};

#endif /* SRC_TMALLA_H_ */