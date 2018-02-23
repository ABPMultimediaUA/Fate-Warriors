#ifndef SRC_TRECURSOMALLA_H_
#define SRC_TRECURSOMALLA_H_
#include "TRecurso.h"
#include <vector>
class Vertex;
class Texture;
class Shader;
class TRecursoMalla : public TRecurso{

public:
    TRecursoMalla(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~TRecursoMalla();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void  cargarFichero(char* nombre);
    void  draw(Shader *shader);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    //float* vertices,*normales,*texturas;
    float* vertTriangulos, *normTriangulos, *texTriangulos;
    long nTriangulos;
    //buffers
    unsigned int VAO, VBO, EBO;

    void Preparar_mesh();
};

#endif /* SRC_TRECURSOMALLA_H_ */