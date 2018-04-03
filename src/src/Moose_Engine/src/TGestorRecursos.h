#ifndef SRC_TGESTORRECURSOS_H_
#define SRC_TGESTORRECURSOS_H_
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
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, const std::string &path);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string &path);
    unsigned int TextureFromFile(const char *path, bool gamma);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene,const std::string path);		
    void cargarAnim(std::string &path, std::vector<TRecursoModelado*> &_i_modelados);
    void cargarModelo(std::string &path,const aiScene* scene, std::vector<TRecursoModelado*> &_i_modelados, const std::string &path_text);
    TRecursoModelado* getRecursoModelo_sinBB(const char* nombre);
    void cargarModelo_sinBB(std::string &path);
    void cargarNodo_sinBB(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, const std::string& path);
    TRecursoMalla* cargarMalla_sinBB(aiMesh *mesh, const aiScene *scene,const std::string path);
private:
    TGestorRecursos();
	std::vector<TRecurso*> _recursos;
    std::string directory;
    static TGestorRecursos* _instancia;


    TRecurso* getRecurso(const char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */