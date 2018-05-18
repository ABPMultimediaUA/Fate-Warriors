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
//la carga de assimp ha sido basada en el codigo de learnopengl
public:
    static TGestorRecursos* get_instancia();
    ~TGestorRecursos();
    //carga de los recursos
    TRecursoModelado* getRecursoModelo(const char* nombre);	
    TRecursoMaterial* getRecursoMaterial(char* nombre);
    TRecursoAnimacion* getRecursoAnim(const char* nombre);

	//carga de animacion
    void cargarAnim(std::string &path, std::vector<TRecursoModelado*> &_i_modelados);
    void cargarModelo(std::string &path,const aiScene* scene, std::vector<TRecursoModelado*> &_i_modelados, const std::string &path_text);

    //carga de modelo
    void cargarModelo(std::string &path);
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, const std::string &path);
    std::vector<TRecursoMaterial*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string &path);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene,const std::string path);
    
    

    void setCalidad(uint8_t _calidad);
private:
    TGestorRecursos();
	std::vector<TRecurso*> _recursos;
    std::string directory;
    static TGestorRecursos* _instancia;
    uint8_t variableCalidad = 1;


    TRecurso* getRecurso(const char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */