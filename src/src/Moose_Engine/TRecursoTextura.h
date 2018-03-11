#ifndef SRC_TRECURSOTEXTURA_H_
#define SRC_TRECURSOTEXTURA_H_
#include "TRecurso.h"

class TRecursoTextura: public TRecurso{

public:
    TRecursoTextura();
    ~TRecursoTextura();
    
    void  SetNombre(char* nombre) override;
    char* GetNombre() override;
    void cargarFichero(char* nombre);
private:
    //pues vete tu a saber que datos tiene una textura xD
};

#endif /* SRC_TRECURSOTEXTURA_H_ */