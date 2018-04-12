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
class TRecursoMaterial;
class TRecursoModelado;
class TRecursoAnimacion;
class aiMesh;
class aiScene;
class aiNode;
class aiMaterial;
class TGestorRecursos {

public:
    static TGestorRecursos* get_instancia();
    ~TGestorRecursos();
    //carga de los recursos
    TRecursoModelado* getRecursoModelo(const char* nombre);	
    TRecursoMaterial* getRecursoMaterial(char* nombre);
    TRecursoAnimacion* getRecursoAnim(const char* nombre);
    TRecursoModelado* getRecursoModelo_sinBB(const char* nombre);

	//carga de animacion
    void cargarAnim(std::string &path, std::vector<TRecursoModelado*> &_i_modelados);
    void cargarModelo(std::string &path,const aiScene* scene, std::vector<TRecursoModelado*> &_i_modelados, const std::string &path_text);

    //carga de modelo
    void cargarModelo(std::string &path);
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, const std::string &path);
    std::vector<TRecursoMaterial*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string &path);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene,const std::string path);
    
    //carga modelo sin Bounding box
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