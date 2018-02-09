#ifndef SRC_TRECURSOMATERIAL_H_
#define SRC_TRECURSOMATERIAL_H_
#include "TRecurso.h"

class TRecursoMaterial : public TRecurso{

public:
    TRecursoMaterial();
    ~TRecursoMaterial();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void cargarFichero(char* nombre);
private:
};

#endif /* SRC_TRECURSOMATERIAL_H_ */