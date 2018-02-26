#ifndef SRC_TGESTORRECURSOS_H_
#define SRC_TGESTORRECURSOS_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <vector>
#include <cstdint>

class TRecurso;
class TRecursoMalla;
class aiMesh;
class aiScene;
class aiNode;
class TGestorRecursos {

public:
    TGestorRecursos();
    ~TGestorRecursos();
    TRecurso* getRecursoMalla(char* nombre, std::vector<TRecursoMalla*> &_i_modelos);	
    TRecurso* getRecursoTextura(char* nombre);	
    TRecurso* getRecursoMaterial(char* nombre);
    void cargarModelo(std::string &path, std::vector<TRecursoMalla*> &_i_modelos);
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene);		
private:
	std::vector<TRecurso*> _recursos;
    
    TRecurso* getRecurso(char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */