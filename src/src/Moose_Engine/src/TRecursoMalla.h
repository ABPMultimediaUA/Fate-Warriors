#ifndef SRC_TRECURSOMALLA_H_
#define SRC_TRECURSOMALLA_H_
#include "TRecurso.h"
#include <vector>
class Vertex;
class Shader;
class TRecursoMaterial;
class TRecursoMalla : public TRecurso{
//el dibujado de opengl esta basado en learnopengl
public:
    TRecursoMalla(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TRecursoMaterial*> textures);
    ~TRecursoMalla();

    std::string GetNombre() override;
    void  SetNombre(std::string nombre) override;
    void  draw(Shader* shader);
    glm::vec3 get_max();
    void set_max(glm::vec3 _i_max);
    glm::vec3 get_min();
    void set_min(glm::vec3 _i_min);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TRecursoMaterial*> textures;
    long nTriangulos;
    //buffers
    unsigned int VAO, VBO, EBO;
    glm::vec3 _max;
    glm::vec3 _min;
    //funciones
    void Preparar_mesh();
};

#endif /* SRC_TRECURSOMALLA_H_ */