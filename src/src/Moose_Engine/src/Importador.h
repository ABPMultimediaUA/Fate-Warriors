#ifndef SRC_IMPORTADOR_H_
#define SRC_IMPORTADOR_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <stack>
class Importer;

class Importador{

public:
	Importador();
	~Importador();
private:
    Assimp::Importer _importer;

};

#endif /* SRC_Importador_H_ */