#ifndef SRC_TGESTORRECURSOS_H_
#define SRC_TGESTORRECURSOS_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <vector>
#include <cstdint>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class TRecurso;
class TRecursoMalla;
class TRecursoModelado;
class aiMesh;
class aiScene;
class aiNode;
class aiMaterial;
class Texture;
class TGestorRecursos {

public:
    static TGestorRecursos* get_instancia();
    ~TGestorRecursos();
    TRecursoModelado* getRecursoModelo(const char* nombre);	
    TRecurso* getRecursoTextura(char* nombre);	
    TRecurso* getRecursoMaterial(char* nombre);
    void cargarModelo(std::string &path);
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, std::string path);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene, std::string path);		
    void cargarAnim(std::string &path, std::vector<TRecursoModelado*> &_i_modelados);
    void cargarModelo(std::string &path,const aiScene* scene, std::vector<TRecursoModelado*> &_i_modelados);
private:
    TGestorRecursos();
	std::vector<TRecurso*> _recursos;
    std::string directory;
    static TGestorRecursos* _instancia;


    TRecurso* getRecurso(const char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */