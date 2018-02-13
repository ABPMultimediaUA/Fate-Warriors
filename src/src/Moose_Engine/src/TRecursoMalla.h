#ifndef SRC_TRECURSOMALLA_H_
#define SRC_TRECURSOMALLA_H_
#include "TRecurso.h"

class TRecursoMalla : public TRecurso{

public:
    TRecursoMalla();
    ~TRecursoMalla();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void  cargarFichero(char* nombre);
    void  draw();

private:
    float* vertices,normales,texturas;
    float* vertTriangulos, normTriangulos, texTriangulos;
    long nTriangulos;
};

#endif /* SRC_TRECURSOMALLA_H_ */