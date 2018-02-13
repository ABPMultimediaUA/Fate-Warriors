#ifndef SRC_TGESTORRECURSOS_H_
#define SRC_TGESTORRECURSOS_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <vector>
#include <cstdint>

class TRecurso;

class TGestorRecursos {

public:
    TGestorRecursos();
    ~TGestorRecursos();
    TRecurso* getRecursoMalla(char* nombre);	
    TRecurso* getRecursoTextura(char* nombre);	
    TRecurso* getRecursoMaterial(char* nombre);		
private:
	std::vector<TRecurso*> _recursos;
    TRecurso* getRecurso(char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */