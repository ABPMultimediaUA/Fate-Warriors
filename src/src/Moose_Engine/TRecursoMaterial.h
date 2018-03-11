#ifndef SRC_TRECURSOMATERIAL_H_
#define SRC_TRECURSOMATERIAL_H_
#include "TRecurso.h"

class aiMaterial;
class TRecursoMaterial : public TRecurso{

public:
    TRecursoMaterial();
    TRecursoMaterial(aiMaterial* _i_material);
    ~TRecursoMaterial();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void cargarFichero(char* nombre);
private:
    aiMaterial* _material;
};

#endif /* SRC_TRECURSOMATERIAL_H_ */